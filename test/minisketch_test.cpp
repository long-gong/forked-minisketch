#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <minisketch_wrapper.h>
#include <vector>

using testing::UnorderedElementsAre;

TEST(MiniSketchTest, Constructor) {
  MiniSketch sketch(12, 4);
  EXPECT_EQ(12, sketch.num_bits());
  EXPECT_EQ(4, sketch.capacity());

  EXPECT_TRUE(sketch.get_sketch_a() != nullptr);
  EXPECT_TRUE(sketch.get_sketch_b() != nullptr);
}

TEST(MiniSketchTest, EncodeAndDecodeSucceed) {

  std::vector<uint32_t> A{101, 1, 1819, 901, 981, 11};
  std::vector<uint32_t> B{101, 1, 1819, 2};
  MiniSketch sketch(12, 4);
  sketch.encode_a(A);
  sketch.encode_b(B);

  EXPECT_EQ(12 * 4 / 8,
            minisketch_serialized_size(sketch.get_sketch_a().get()));
  EXPECT_EQ(12 * 4 / 8,
            minisketch_serialized_size(sketch.get_sketch_b().get()));

#ifdef USE_CXX17
  auto diff = sketch.decode().value();
#else
  auto diff = sketch.decode();
#endif

  EXPECT_THAT(diff, UnorderedElementsAre(901, 981, 11, 2));
}

TEST(MiniSketchTest, EncodeAndDecodeFail) {

  std::vector<uint32_t> A{101, 1, 1819, 901, 981, 11, 100};
  std::vector<uint32_t> B{101, 1, 1819, 2};
  MiniSketch sketch(12, 4);
  sketch.encode_a(A);
  sketch.encode_b(B);

  EXPECT_EQ(12 * 4 / 8,
            minisketch_serialized_size(sketch.get_sketch_a().get()));
  EXPECT_EQ(12 * 4 / 8,
            minisketch_serialized_size(sketch.get_sketch_b().get()));
#ifdef USE_CXX17
  auto diff = sketch.decode();
  EXPECT_TRUE(diff == std::nullopt);
#else
  EXPECT_THROW(sketch.decode(), std::exception);
#endif
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
