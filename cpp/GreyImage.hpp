#ifndef GREYIMAGE_HPP
#define GREYIMAGE_HPP

#include "Image.hpp"

typedef uint8_t GreyPixel;

class GreyImage : public Image<GreyPixel> {
public:
  GreyImage(const Size width, const Size height);
  GreyImage(const Image<GreyPixel> &image);

  void writePGM(std::ostream &os) const;
  static GreyImage *readPGM(std::istream &is);

  GreyImage *simpleScale(const Size width, const Size height) const;
  GreyImage *bilinearScale(const Size width, const Size height) const;
};

typedef GreyImage GrayImage;

#endif
