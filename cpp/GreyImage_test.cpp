#include <iostream>
#include <fstream>
#include "GreyImage.hpp"

using namespace std;

int main()
{
	ifstream catFile("cat.pgm", std::ios::binary);
  GreyImage *catImage = GreyImage::readPGM(catFile);

  catImage->rectangle(10, 10, 300, 200, 100);
  catImage->rectangle(15, 15, 280, 180, 250);
  catImage->rectangle(20, 20, 270, 170, 50);

  catImage->fillRectangle(90, 85, 40, 20, 10);
  catImage->fillRectangle(190, 87, 40, 20, 255);

  ofstream catSave("cat_out.pgm", std::ios::binary | std::ios::out);

  catImage->writePGM(catSave);

  delete catImage;


	return 0;
}
