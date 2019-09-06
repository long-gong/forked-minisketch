#ifndef _MINISKETCH_WRAPPER_H_
#define _MINISKETCH_WRAPPER_H_

#include "minisketch.h"
#if defined(USE_SPDLOG)
#include <spdlog/spdlog.h>
#endif

#include <memory>
#include <stdexcept>
#include <vector>

#if __cplusplus == 201703L
#define USE_CXX17
#endif

#ifdef USE_CXX17
#include <optional>
#endif

namespace {
constexpr auto MINI_SKETCH_IMPL = 0;
} // namespace

struct MiniSketchDeleter { // deleter
  void operator()(minisketch *sketch) const {
#if defined(USE_SPDLOG)
    spdlog::debug("Destroy a minisketch with {}",
                  minisketch_serialized_size(sketch));
#endif
    minisketch_destroy(sketch);
  };
};

namespace minisketch_wrapper {
struct MiniSketch {
  using element_t = uint32_t;
  using ustring_t = std::basic_string<unsigned char>;

  // create an empty minisketch
  MiniSketch(unsigned m, unsigned t)
      : m_(m), t_(t), sketch_(minisketch_create(m, MINI_SKETCH_IMPL, t),
                              MiniSketchDeleter()) {}

  static MiniSketch deserialize_from(unsigned m, unsigned t,
                                     const ustring_t &buffer) {
    std::unique_ptr<minisketch, MiniSketchDeleter> sketch(
        minisketch_create(m, MINI_SKETCH_IMPL, t), MiniSketchDeleter());
    minisketch_deserialize(sketch.get(), &buffer[0]);
    return MiniSketch(m, t, std::move(sketch));
  }

  size_t num_bits() const { return m_; }
  size_t capacity() const { return t_; }

  // preferred
  MiniSketch &operator^=(const MiniSketch &other) { return merge_with(other); }

  MiniSketch operator^(const MiniSketch &other) {
    std::unique_ptr<minisketch, MiniSketchDeleter> merged(
        minisketch_clone(sketch_.get()));
    minisketch_merge(merged.get(), other.get_sketch().get());
    return MiniSketch(m_, t_, std::move(merged));
  }

  MiniSketch &merge_with(const MiniSketch &other) {
    minisketch_merge(sketch_.get(), other.get_sketch().get());
    return *this;
  }

  const std::unique_ptr<minisketch, MiniSketchDeleter> &get_sketch() const {
    return sketch_;
  }

  ustring_t serialize() const {
    size_t sersize = minisketch_serialized_size(sketch_.get());
    assert(sersize == m_ * t_ / 8);
    ustring_t buffer(sersize, '\0');
    minisketch_serialize(sketch_.get(), &buffer[0]);
    return buffer;
  }

  void add(element_t s) { minisketch_add_uint64(sketch_.get(), s); }

  void encode(const std::vector<element_t> &S) {
    for (auto s : S) {
      add(s);
    }
  }

#ifdef USE_CXX17
  std::optional<std::vector<uint64_t>> decode() {
#else
  std::vector<uint64_t> decode() {
#endif
    std::vector<uint64_t> differences(t_, 0);
    ssize_t num_differences =
        minisketch_decode(sketch_.get(), t_, &differences[0]);
    if (num_differences < 0) {
#ifdef USE_CXX17
      return std::nullopt;
#else
      throw std::runtime_error("Unable to decode");
#endif
    }
    if (num_differences < t_) {
      differences.erase(differences.begin() + num_differences,
                        differences.end());
    }
    return differences;
  }

protected:
  MiniSketch(unsigned m, unsigned t,
             std::unique_ptr<minisketch, MiniSketchDeleter> init)
      : m_(m), t_(t), sketch_(std::move(init)) {}

private:
  unsigned m_; // # of bits
  unsigned t_; // capacity

  std::unique_ptr<minisketch, MiniSketchDeleter> sketch_;
};
} // namespace minisketch_wrapper

struct MiniSketch {
  using element_t = uint32_t;
  MiniSketch(unsigned m, unsigned t)
      : m_(m), t_(t), sketch_a_(minisketch_create(m, MINI_SKETCH_IMPL, t),
                                MiniSketchDeleter()),
        sketch_b_(minisketch_create(m, MINI_SKETCH_IMPL, t),
                  MiniSketchDeleter()) {}
  size_t num_bits() const { return m_; }
  size_t capacity() const { return t_; }
  const std::unique_ptr<minisketch, MiniSketchDeleter> &get_sketch_a() const {
    return sketch_a_;
  }
  const std::unique_ptr<minisketch, MiniSketchDeleter> &get_sketch_b() const {
    return sketch_b_;
  }
  void encode_a(const std::vector<element_t> &A) { _encode(A, sketch_a_); }
  void encode_b(const std::vector<element_t> &B) { _encode(B, sketch_b_); }

#ifdef USE_CXX17
  std::optional<std::vector<uint64_t>> decode() {
#else
  std::vector<uint64_t> decode() {
#endif
    // Merge the elements from sketch_a into sketch_b. The result is a sketch_b
    // which contains all elements that occurred in Alice's or Bob's sets, but
    // not in both.
    minisketch_merge(sketch_b_.get(), sketch_a_.get());
    std::vector<uint64_t> differences(t_, 0);
    ssize_t num_differences =
        minisketch_decode(sketch_b_.get(), t_, &differences[0]);
    if (num_differences < 0) {
#ifdef USE_CXX17
      return std::nullopt;
#else
      throw std::runtime_error("Unable to decode");
#endif
    }
    if (num_differences < t_) {
      differences.erase(differences.begin() + num_differences,
                        differences.end());
    }
    return differences;

    //    std::vector<element_t > diff;
    //    diff.reserve(num_differences);
    //    for(size_t i = 0;i < num_differences;++ i) {
    //      diff.push_back(differences[i]);
    //    }
    //    return diff;
  }

private:
  static void _encode(const std::vector<element_t> &S,
                      std::unique_ptr<minisketch, MiniSketchDeleter> &sketch) {
    for (auto s : S) {
      minisketch_add_uint64(sketch.get(), s);
    }
  }

  unsigned m_; // # of bits
  unsigned t_; // capacity

  std::unique_ptr<minisketch, MiniSketchDeleter> sketch_a_;
  std::unique_ptr<minisketch, MiniSketchDeleter> sketch_b_;
};
#endif // _MINISKETCH_WRAPPER_H_