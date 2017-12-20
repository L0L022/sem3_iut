#ifndef COLORIMAGE_HPP
#define COLORIMAGE_HPP

#include "Image.hpp"
#include <cmath>
#include <string>

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

  ColorPixel operator+(const ColorPixel &cp) const {
    return ColorPixel(red + cp.red, green + cp.green, blue + cp.blue);
  }

  ColorPixel operator*(const double v) const {
    return ColorPixel(red * v, green * v, blue * v);
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

  void writeJPEG(std::ostream &os, unsigned int quality = 75) const;
  void writeJPEG(const std::string &fileName, unsigned int quality = 75) const;
  void writeJPEG(const char *fileName, unsigned int quality = 75) const;
  static ColorImage *readJPEG(std::istream &is);
  static ColorImage *readJPEG(const std::string &fileName);
  static ColorImage *readJPEG(const char *fileName);

  void writeTGA(std::ostream &os, bool rle = true) const;
  static ColorImage *readTGA(std::istream &is);

  static ColorImage *readMaison2(std::istream &is);

  ColorImage *anaglyphe() const;
};

std::ostream &operator<<(std::ostream &os, const ColorPixel &pixel);
std::istream &operator>>(std::istream &is, ColorPixel &pixel);

#endif
