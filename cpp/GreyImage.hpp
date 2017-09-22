#ifndef GREYIMAGE_HPP
#define GREYIMAGE_HPP

#include "Image.hpp"

// class GreyPixel
// {
//   typedef uint8_t PixelType;
//
//   GreyPixel(const PixelType value = 0);
//
// private:
//   PixelType m_value;
// };
typedef uint8_t GreyPixel;
typedef Image<GreyPixel> GreyImage;
typedef GreyImage GrayImage;

std::ostream &operator<<(std::ostream &os, const GreyPixel &pixel);

#endif
