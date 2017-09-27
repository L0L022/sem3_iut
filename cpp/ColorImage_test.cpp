#include <iostream>
#include <fstream>
#include "ColorImage.hpp"

using namespace std;

int main() {
  ColorImage empty(10, 10);
  empty.fill(1);
  empty.pixel(0, 0) = 10;
  empty.pixel(5, 2) = 10;
  empty.pixel(9, 9) = 10;

  ColorImage copy(empty);
  copy.clear();
  copy.rectangle(0, 0, 5, 5, 12);

  ColorImage copy2(copy);
  copy2.fillRectangle(5, 5, 2, 2, ColorPixel(255, 0, 0));
  copy2.pixel(0, 0) = 65;
  copy2.pixel(1, 0) = 66;
  copy2.pixel(2, 0) = 67;
  copy2.pixel(7, 9) = 88;
  copy2.pixel(8, 9) = 89;
  copy2.pixel(9, 9) = 90;

  cout << empty << endl
       << copy << endl
       << copy2 << endl;

  fstream save;
  save.open("out.ppm", std::ios::out | std::ios::binary);
  if (save.is_open()) {
  	copy2.writePPM(save);
  }

  return 0;
}
