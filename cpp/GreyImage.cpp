#include <iostream>
#include "Image.hpp"

using namespace std;

int main()
{
	Image empty(10, 10);
	empty.fill(1);
	empty.pixel(0, 0) = 10;
	empty.pixel(5, 2) = 10;
	empty.pixel(9, 9) = 10;

	Image copy(empty);
	copy.clear();
	copy.rectangle(0, 0, 5, 5, 12);

	cout << empty << endl
	<< copy << endl;
	return 0;
}
