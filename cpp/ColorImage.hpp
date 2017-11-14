#ifndef COLORIMAGE_HPP
#define COLORIMAGE_HPP

#include "Image.hpp"

struct ColorPixel {
  uint8_t red, green, blue;

  ColorPixel()
  : red(0), green(0), blue(0)
  {}

  ColorPixel(const uint red, const uint green, const uint blue)
  : red(red), green(green), blue(blue)
  {}

  ColorPixel(const uint value)
  : red(value), green(value), blue(value)
  {}

  ColorPixel& operator=(const uint8_t value)
  {
    red = value;
    green = value;
    blue = value;
    
    return *this;
  }
};

class ColorImage : public Image<ColorPixel>
{
public:
  ColorImage(const Size width, const Size height);
  ColorImage(const Image<ColorPixel> &image);

  ColorImage* simpleScale(const Size width, const Size height) const;

  void writePPM(std::ostream &os) const;
  static ColorImage* readPPM(std::istream &is);

  void writeJPEG(std::ostream &os, int quality = 75) const;
  static ColorImage* readJPEG(std::istream &is);
};

std::ostream &operator<<(std::ostream &os, const ColorPixel &pixel);
std::istream &operator>>(std::istream &is, ColorPixel &pixel);

#endif
