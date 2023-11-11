#pragma once
#ifndef IMAGEEDITOR_CORE_TEST_H
#define IMAGEEDITOR_CORE_TEST_H
#include "Core/Image/Image.h"

#include <gtest/gtest.h>

namespace Core_Image_Tests {

TEST(Image_Test, Constructor_Test) {
  using namespace ImageEditor::Core;
  ByteArr data(24, 0);
  Image image(Image::Parameters{
      .data = data, .width = 4, .height = 8, .bytes_per_line = 4, .format = 0

  });
  EXPECT_EQ(image.Width(), 4);
  EXPECT_EQ(image.Height(), 8);
  EXPECT_EQ(image.BytesPerLine(), 4);
  EXPECT_EQ(image.Format(), 0);
}

} // namespace Core_Image_Tests

#endif // IMAGEEDITOR_CORE_TEST_H
