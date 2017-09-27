#include <iostream>
#include <fstream>
#include "ColorImage.hpp"

using namespace std;

int main() {
  ifstream catFile("cat.ppm", std::ios::binary);
  ColorImage *catImage = ColorImage::readPPM(catFile);

  catImage->rectangle(10, 10, 300, 200, ColorPixel(255, 0, 0));
  catImage->rectangle(15, 15, 280, 180, ColorPixel(0, 255, 0));
  catImage->rectangle(20, 20, 270, 170, ColorPixel(0, 0, 255));

  catImage->fillRectangle(90, 85, 40, 20, ColorPixel(234, 120, 200));
  catImage->fillRectangle(190, 87, 40, 20, ColorPixel(234, 120, 200));

  ofstream catSave("cat_out.ppm", std::ios::binary | std::ios::out);

  catImage->writePPM(catSave);

  delete catImage;

  return 0;
}
