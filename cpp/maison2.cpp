#include "ColorImage.hpp"
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

int main() {
  ifstream inputFile("chat.ma2", std::ios::binary);
  ColorImage *catImage = ColorImage::readMaison2(inputFile);
  inputFile.close();
  //
  // catImage->rectangle(10, 10, 300, 200, ColorPixel(255, 0, 0));
  // catImage->rectangle(15, 15, 280, 180, ColorPixel(0, 255, 0));
  // catImage->rectangle(20, 20, 270, 170, ColorPixel(0, 0, 255));
  //
  // catImage->fillRectangle(90, 85, 40, 20, ColorPixel(234, 120, 200));
  // catImage->fillRectangle(190, 87, 40, 20, ColorPixel(234, 120, 200));
  //
  // catImage->circle(109, 94, 20, ColorPixel(255, 0, 0));
  // catImage->circle(212, 99, 20, ColorPixel(255, 0, 0));
  // catImage->fillCircle(150, 96, 10, ColorPixel(0, 255, 0));

  ofstream outputFile("ma2_chat.ppm", std::ios::binary | std::ios::out);
  catImage->writePPM(outputFile);
  outputFile.close();

  delete catImage;
  catImage = nullptr;

  inputFile.open("colibri.ma2", std::ios::binary);
  catImage = ColorImage::readMaison2(inputFile);
  inputFile.close();

  // catImage->rectangle(10, 10, 300, 200, ColorPixel(255, 0, 0));
  // catImage->rectangle(15, 15, 280, 180, ColorPixel(0, 255, 0));
  // catImage->rectangle(20, 20, 270, 170, ColorPixel(0, 0, 255));
  //
  // catImage->fillRectangle(90, 85, 40, 20, ColorPixel(234, 120, 200));
  // catImage->fillRectangle(190, 87, 40, 20, ColorPixel(234, 120, 200));
  //
  // catImage->circle(109, 94, 20, ColorPixel(255, 0, 0));
  // catImage->circle(212, 99, 20, ColorPixel(255, 0, 0));
  // catImage->fillCircle(150, 96, 10, ColorPixel(0, 255, 0));

  outputFile.open("ma2_colibri.tga", std::ios::binary | std::ios::out);
  catImage->writeTGA(outputFile);
  outputFile.close();

  delete catImage;
  catImage = nullptr;

  inputFile.open("lena.ma2", std::ios::binary);
  catImage = ColorImage::readMaison2(inputFile);
  inputFile.close();

  // catImage->rectangle(10, 10, 300, 200, ColorPixel(255, 0, 0));
  // catImage->rectangle(15, 15, 280, 180, ColorPixel(0, 255, 0));
  // catImage->rectangle(20, 20, 270, 170, ColorPixel(0, 0, 255));
  //
  // catImage->fillRectangle(90, 85, 40, 20, ColorPixel(234, 120, 200));
  // catImage->fillRectangle(190, 87, 40, 20, ColorPixel(234, 120, 200));
  //
  // catImage->circle(109, 94, 20, ColorPixel(255, 0, 0));
  // catImage->circle(212, 99, 20, ColorPixel(255, 0, 0));
  // catImage->fillCircle(150, 96, 10, ColorPixel(0, 255, 0));

  outputFile.open("ma2_lena.tga", std::ios::binary | std::ios::out);
  catImage->writeTGA(outputFile);
  outputFile.close();

  delete catImage;
  catImage = nullptr;

  return 0;
}
