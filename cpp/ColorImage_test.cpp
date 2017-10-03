#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
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

  catImage->cercle(109, 94, 20, ColorPixel(255, 0, 0));
  catImage->cercle(212, 99, 20, ColorPixel(255, 0, 0 ));

  ofstream catSave("cat_out.ppm", std::ios::binary | std::ios::out);

  catImage->writePPM(catSave);

  ofstream catSaveJPEG("cat_out.jpeg", std::ios::binary | std::ios::out);

  catImage->writeJPEG(catSaveJPEG);

  delete catImage;
  catImage = nullptr;
  catFile.close();
  catSaveJPEG.close();

  catFile.open("cat_out.jpeg", std::ios::binary);
  catImage = ColorImage::readJPEG(catFile);

  catImage->fillRectangle(140, 155, 40, 20, ColorPixel(255, 28, 28));

  catSaveJPEG.open("cat_out_2.jpeg", std::ios::binary | std::ios::out);
  catImage->writeJPEG(catSaveJPEG, 100);

  std::srand(std::time(0));
  for(unsigned int quality = 0; quality <= 100; quality += 5)  {
    std::ostringstream oss; // Variable pour former le nom de chaque fichier.
    oss << "cat_out_" << std::setfill('0') << std::setw(3) << quality << ".jpg";

    ofstream save(oss.str().c_str(), std::ios::binary | std::ios::out);

    size_t x=std::rand()%catImage->width(), y=std::rand()%catImage->height();
    catImage->fillRectangle(
      x, y,
      std::rand()%(catImage->width()-x), std::rand()%(catImage->height()-y),
      ColorPixel(std::rand()%255, std::rand()%255, std::rand()%255));
    catImage->writeJPEG(save, quality);
  }

  delete catImage;

  return 0;
}
