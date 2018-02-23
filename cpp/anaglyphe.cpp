#include "ColorImage.hpp"
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

int main() {
  ifstream inputFile("temple.ppm", std::ios::binary);
  ColorImage *catImage = ColorImage::readPPM(inputFile);
  inputFile.close();

  ColorImage *ana = catImage->anaglyphe();

  ofstream outputFile("ana_temple.ppm", std::ios::binary | std::ios::out);
  ana->writePPM(outputFile);
  outputFile.close();

  delete catImage;
  catImage = nullptr;
  delete ana;

  inputFile.open("ombres.ppm", std::ios::binary);
  catImage = ColorImage::readPPM(inputFile);
  inputFile.close();

  ana = catImage->anaglyphe();

  outputFile.open("ana_ombres.ppm", std::ios::binary | std::ios::out);
  ana->writePPM(outputFile);
  outputFile.close();

  delete catImage;
  catImage = nullptr;
  delete ana;

  return 0;
}
