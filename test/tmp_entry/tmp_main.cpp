#include <iostream>
#include <ndclibs.hpp>

int main(int argc, char **argv)
{
  BitmapImage image(100, 100);
  image.WriteBmp("test.bmp");
  return 0;
}
