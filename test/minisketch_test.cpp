#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <minisketch_wrapper.h>
#include <vector>

using testing::UnorderedElementsAre;

// TEST(MiniSketchTest, Constructor) {
//   MiniSketch sketch(12, 4);
//   EXPECT_EQ(12, sketch.num_bits());
//   EXPECT_EQ(4, sketch.capacity());

//   EXPECT_TRUE(sketch.get_sketch_a() != nullptr);
//   EXPECT_TRUE(sketch.get_sketch_b() != nullptr);
// }

// TEST(MiniSketchTest, EncodeAndDecodeSucceed) {

//   std::vector<uint32_t> A{101, 1, 1819, 901, 981, 11};
//   std::vector<uint32_t> B{101, 1, 1819, 2};
//   MiniSketch sketch(12, 4);
//   sketch.encode_a(A);
//   sketch.encode_b(B);

//   EXPECT_EQ(12 * 4 / 8,
//             minisketch_serialized_size(sketch.get_sketch_a().get()));
//   EXPECT_EQ(12 * 4 / 8,
//             minisketch_serialized_size(sketch.get_sketch_b().get()));

// #ifdef USE_CXX17
//   auto diff = sketch.decode().value();
// #else
//   auto diff = sketch.decode();
// #endif

//   EXPECT_THAT(diff, UnorderedElementsAre(901, 981, 11, 2));
// }

// TEST(MiniSketchTest, EncodeAndDecodeFail) {

//   std::vector<uint32_t> A{101, 1, 1819, 901, 981, 11, 100};
//   std::vector<uint32_t> B{101, 1, 1819, 2};
//   MiniSketch sketch(12, 4);
//   sketch.encode_a(A);
//   sketch.encode_b(B);

//   EXPECT_EQ(12 * 4 / 8,
//             minisketch_serialized_size(sketch.get_sketch_a().get()));
//   EXPECT_EQ(12 * 4 / 8,
//             minisketch_serialized_size(sketch.get_sketch_b().get()));
// #ifdef USE_CXX17
//   auto diff = sketch.decode();
//   EXPECT_TRUE(diff == std::nullopt);
// #else
//   EXPECT_THROW(sketch.decode(), std::exception);
// #endif
// }

using MiniSketchV2 = minisketch_wrapper::MiniSketch;
TEST(MiniSketchV2Test, Constructor) {
  MiniSketchV2 sketch(12, 4);
  EXPECT_EQ(12, sketch.num_bits());
  EXPECT_EQ(4, sketch.capacity());

  EXPECT_TRUE(sketch.get_sketch() != nullptr);
}

TEST(MiniSketchV2Test, ConstructByDeserilization) {
  MiniSketchV2 sketch(12, 4);
  for (uint32_t elem = 100; elem < 104;++ elem) {
    sketch.add(elem);
  }
  auto buffer = sketch.serialize();
  auto sketch_b = MiniSketchV2::deserialize_from(12, 4, buffer);
  EXPECT_EQ(buffer, sketch_b.serialize());
}

TEST(MiniSketchV2Test, EncodeAndDecode) {
  MiniSketchV2 sketch(12, 4);
  for (uint32_t elem = 100; elem < 104;++ elem) {
    sketch.add(elem);
  }
  {
    auto diff = sketch.decode();
    EXPECT_TRUE(diff.has_value());
    EXPECT_THAT(diff.value(), UnorderedElementsAre(100, 101, 102, 103));
  }
  {
    sketch.add(104);
    auto diff = sketch.decode();
    EXPECT_FALSE(diff);
  }
}

TEST(MiniSketchV2Test, XOR) {
  MiniSketchV2 sketch_a(12, 4);
  MiniSketchV2 sketch_b(12, 4);
  std::vector<uint32_t > A{100, 101, 102, 103};
  std::unordered_set<uint32_t > B{100, 101, 104, 105};

  sketch_a.encode(A);
  sketch_b.encode(B);

  {
    auto sketch = sketch_a ^ sketch_b;
    EXPECT_EQ(12, sketch.num_bits());
    EXPECT_EQ(4, sketch.capacity());
    auto diff = sketch.decode();
    EXPECT_TRUE(diff.has_value());
    EXPECT_THAT(diff.value(), UnorderedElementsAre(102, 103, 104, 105));
  }

  {
    sketch_a ^= sketch_b;
    auto diff = sketch_a.decode();
    EXPECT_THAT(diff.value(), UnorderedElementsAre(102, 103, 104, 105));
  }

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
