#include "Image.hpp"

std::ostream &operator<<(std::ostream &os, const uint8_t &value)
{
  // double grey = pixel / static_cast<double>(std::numeric_limits<GreyPixel>::max());
  // if (grey > 0.8)
  //   os << "█";
  // else if (grey > 0.6)
  //   os << "▓";
  // else if (grey > 0.4)
  //   os << "▒";
  // else if (grey > 0.2)
  //   os << "░";
  // else
  //   os << " ";
  // return os;

  return os << static_cast<short>(value);
}

std::istream &operator>>(std::istream &is, uint8_t &value)
{
  short v;
  is >> v;
  value = v;
  return is;
}
