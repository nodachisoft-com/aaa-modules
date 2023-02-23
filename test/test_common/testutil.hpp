#pragma once
#include <ndclibs.hpp>

namespace TestUtil
{

  static void drawHfColorful(Memory2d<float> *hf, std::string filepath)
  {
    int width = hf->getWidth();
    int height = hf->getHeight();
    BitmapImage image(width, height);
    for (int v = 0; v < height; v++)
    {
      for (int u = 0; u < width; u++)
      {
        float res = hf->getWithIgnoreOutOfRangeData(u, v);
        unsigned char color_elem = (unsigned char)res;
        ColorRGB color{color_elem, color_elem, color_elem};
        image.set(u, v, color);
      }
    }
    image.WriteBmp("./debug/0000_test.bmp");
  }
}
