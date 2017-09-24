#ifndef GREYIMAGE_HPP
#define GREYIMAGE_HPP

#include "Image.hpp"

typedef uint8_t GreyPixel;

class GreyImage : public Image<GreyPixel>
{
public:
  GreyImage(const Size width, const Size height);

  void writePGM(std::ostream &os) const;
  static GreyImage* readPGM(std::istream &is);
};

typedef GreyImage GrayImage;

std::ostream &operator<<(std::ostream &os, const uint8_t &value);

#endif
