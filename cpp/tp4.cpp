#include "ColorImage.hpp"
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

int main() {
  ifstream catFile("cat_ascii.ppm", std::ios::binary);
  ColorImage *catImage = ColorImage::readPPM(catFile);
  catFile.close();

  catImage->rectangle(10, 10, 300, 200, ColorPixel(255, 0, 0));
  catImage->rectangle(15, 15, 280, 180, ColorPixel(0, 255, 0));
  catImage->rectangle(20, 20, 270, 170, ColorPixel(0, 0, 255));

  catImage->fillRectangle(90, 85, 40, 20, ColorPixel(234, 120, 200));
  catImage->fillRectangle(190, 87, 40, 20, ColorPixel(234, 120, 200));

  catImage->circle(109, 94, 20, ColorPixel(255, 0, 0));
  catImage->circle(212, 99, 20, ColorPixel(255, 0, 0));
  catImage->fillCircle(150, 96, 10, ColorPixel(0, 255, 0));

  ofstream catSave("tp4_ascii.tga", std::ios::binary | std::ios::out);
  catImage->writeTGA(catSave);
  catSave.close();

  delete catImage;
  catImage = nullptr;

  catFile.open("chat.tga", std::ios::binary);
  catImage = ColorImage::readTGA(catFile);
  catFile.close();

  catImage->rectangle(10, 10, 300, 200, ColorPixel(255, 0, 0));
  catImage->rectangle(15, 15, 280, 180, ColorPixel(0, 255, 0));
  catImage->rectangle(20, 20, 270, 170, ColorPixel(0, 0, 255));

  catImage->fillRectangle(90, 85, 40, 20, ColorPixel(234, 120, 200));
  catImage->fillRectangle(190, 87, 40, 20, ColorPixel(234, 120, 200));

  catImage->circle(109, 94, 20, ColorPixel(255, 0, 0));
  catImage->circle(212, 99, 20, ColorPixel(255, 0, 0));
  catImage->fillCircle(150, 96, 10, ColorPixel(0, 255, 0));

  catSave.open("tp4_from_chat_tga.tga", std::ios::binary | std::ios::out);
  catImage->writeTGA(catSave);
  catSave.close();

  delete catImage;
  catImage = nullptr;

  catFile.open("chat010couleurs.tga", std::ios::binary);
  catImage = ColorImage::readTGA(catFile);
  catFile.close();

  catImage->rectangle(10, 10, 300, 200, ColorPixel(255, 0, 0));
  catImage->rectangle(15, 15, 280, 180, ColorPixel(0, 255, 0));
  catImage->rectangle(20, 20, 270, 170, ColorPixel(0, 0, 255));

  catImage->fillRectangle(90, 85, 40, 20, ColorPixel(234, 120, 200));
  catImage->fillRectangle(190, 87, 40, 20, ColorPixel(234, 120, 200));

  catImage->circle(109, 94, 20, ColorPixel(255, 0, 0));
  catImage->circle(212, 99, 20, ColorPixel(255, 0, 0));
  catImage->fillCircle(150, 96, 10, ColorPixel(0, 255, 0));

  catSave.open("tp4_from_chat010couleurs_tga.tga",
               std::ios::binary | std::ios::out);
  catImage->writeTGA(catSave);
  catSave.close();

  delete catImage;
  catImage = nullptr;

  catFile.open("palette_bl.tga", std::ios::binary);
  catImage = ColorImage::readTGA(catFile);
  catFile.close();

  catImage->rectangle(10, 10, 300, 200, ColorPixel(255, 0, 0));
  catImage->rectangle(15, 15, 280, 180, ColorPixel(0, 255, 0));
  catImage->rectangle(20, 20, 270, 170, ColorPixel(0, 0, 255));

  catImage->fillRectangle(90, 85, 40, 20, ColorPixel(234, 120, 200));
  catImage->fillRectangle(190, 87, 40, 20, ColorPixel(234, 120, 200));

  catImage->circle(109, 94, 20, ColorPixel(255, 0, 0));
  catImage->circle(212, 99, 20, ColorPixel(255, 0, 0));
  catImage->fillCircle(150, 96, 10, ColorPixel(0, 255, 0));

  catSave.open("from_palette_bl.tga",
               std::ios::binary | std::ios::out);
  catImage->writeTGA(catSave);
  catSave.close();

  delete catImage;
  catImage = nullptr;

  catFile.open("palette_tl.tga", std::ios::binary);
  catImage = ColorImage::readTGA(catFile);
  catFile.close();

  catImage->rectangle(10, 10, 300, 200, ColorPixel(255, 0, 0));
  catImage->rectangle(15, 15, 280, 180, ColorPixel(0, 255, 0));
  catImage->rectangle(20, 20, 270, 170, ColorPixel(0, 0, 255));

  catImage->fillRectangle(90, 85, 40, 20, ColorPixel(234, 120, 200));
  catImage->fillRectangle(190, 87, 40, 20, ColorPixel(234, 120, 200));

  catImage->circle(109, 94, 20, ColorPixel(255, 0, 0));
  catImage->circle(212, 99, 20, ColorPixel(255, 0, 0));
  catImage->fillCircle(150, 96, 10, ColorPixel(0, 255, 0));

  catSave.open("from_palette_tl.tga",
               std::ios::binary | std::ios::out);
  catImage->writeTGA(catSave);
  catSave.close();

  delete catImage;
  catImage = nullptr;

  return 0;
}
