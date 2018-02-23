#include "GreyImage.hpp"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
  {
    ifstream catFile("cat_ascii.pgm", std::ios::binary);

    GreyImage *catImage = GreyImage::readPGM(catFile);

    catImage->rectangle(10, 10, 300, 200, 100);
    catImage->rectangle(15, 15, 280, 180, 250);
    catImage->rectangle(20, 20, 270, 170, 50);

    catImage->fillRectangle(90, 85, 40, 20, 10);
    catImage->fillRectangle(190, 87, 40, 20, 255);

    catImage->line(150, 150, 100, 200, 0);
    catImage->line(150, 150, 200, 200, 0);

    ofstream catSave("tp1_ascii.pgm", std::ios::binary | std::ios::out);

    catImage->writePGM(catSave);

    delete catImage;
  }
  {
    ifstream catFile("cat_brut.pgm", std::ios::binary);

    GreyImage *catImage = GreyImage::readPGM(catFile);

    catImage->rectangle(10, 10, 300, 200, 100);
    catImage->rectangle(15, 15, 280, 180, 250);
    catImage->rectangle(20, 20, 270, 170, 50);

    catImage->fillRectangle(90, 85, 40, 20, 10);
    catImage->fillRectangle(190, 87, 40, 20, 255);

    ofstream catSave("tp1_brut.pgm", std::ios::binary | std::ios::out);

    catImage->writePGM(catSave);

    delete catImage;
  }

  return 0;
}
