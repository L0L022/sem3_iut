#include <iostream>
#include <fstream>
#include "GreyImage.hpp"

using namespace std;

int main()
{
	GreyImage empty(10, 10);
	empty.fill(1);
	empty.pixel(0, 0) = 10;
	empty.pixel(5, 2) = 10;
	empty.pixel(9, 9) = 10;

	GrayImage copy(empty);
	copy.clear();
	copy.rectangle(0, 0, 5, 5, 12);

	GreyImage copy2(copy);
	copy2.fillRectangle(5, 5, 2, 2, 8);
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
	save.open("out.pgm", std::ios::out | std::ios::binary);
	// if (save.is_open()) {
	// 	copy2.writePGM(save);
	// }
	fstream load;
	load.open("chat.pgm", std::ios::in | std::ios::binary);
	if (load.is_open()) {
		GreyImage *image = GreyImage::readPGM(load);

		cout << std::hex << *image << endl;

		image->fillRectangle(100, 100, 50, 30, 125);
cout << std::oct;
		if (save.is_open())
			image->writePGM(save);

		delete image;
	}

	return 0;
}
