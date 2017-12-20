#ifndef COLORIMAGE_HPP
#define COLORIMAGE_HPP

#include "Image.hpp"
#include <cmath>

class ColorPixel {
public:
  uint8_t red, green, blue;

  ColorPixel() : red(0), green(0), blue(0) {}

  ColorPixel(const uint red, const uint green, const uint blue)
      : red(red), green(green), blue(blue) {}

  ColorPixel(const uint value) : red(value), green(value), blue(value) {}

  ColorPixel &operator=(const uint8_t value) {
    red = value;
    green = value;
    blue = value;

    return *this;
  }

  bool operator==(const ColorPixel &cp) const {
    return red == cp.red and green == cp.green and blue == cp.blue;
  }

  bool almostEqual(const ColorPixel &cp) const {
    return almostEqual(red, cp.red) and almostEqual(green, cp.green) and
           almostEqual(blue, cp.blue);
  }

  ColorPixel operator+(const ColorPixel &cp) const {
    return ColorPixel(red + cp.red, green + cp.green, blue + cp.blue);
  }

  ColorPixel operator*(const double v) const {
    return ColorPixel(red * v, green * v, blue * v);
  }

private:
  bool almostEqual(const uint8_t n1, const uint8_t n2) const {
    return std::abs(n1 - n2) < 5;
  }
};

typedef ColorPixel Color;

class ColorImage : public Image<ColorPixel> {
public:
  ColorImage(const Size width, const Size height);
  ColorImage(const Image<ColorPixel> &image);

  ColorImage *simpleScale(const Size width, const Size height) const;
  ColorImage *bilinearScale(const Size width, const Size height) const;

  void writePPM(std::ostream &os) const;
  static ColorImage *readPPM(std::istream &is);

  void writeJPEG(std::ostream &os, int quality = 75) const;
  static ColorImage *readJPEG(std::istream &is);

  void writeTGA(std::ostream &os, bool rle = true) const;
  static ColorImage *readTGA(std::istream &is);
};

std::ostream &operator<<(std::ostream &os, const ColorPixel &pixel);
std::istream &operator>>(std::istream &is, ColorPixel &pixel);

#endif
