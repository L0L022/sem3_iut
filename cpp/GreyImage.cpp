#include "GreyImage.hpp"
#include "Toolbox.hpp"
#include <limits>
#include <sstream>

GreyImage::GreyImage(const Size width, const Size height)
: Image<GreyPixel>(width, height)
{}

void GreyImage::writePGM(std::ostream &os) const
{
  std::stringstream ss;
  ss << "P5\n"
     << width() << ' ' << height() << '\n'
     << std::numeric_limits<GreyPixel>::max() << '\n';

  for (size_t y = 0; y < height(); y++)
    for (size_t x = 0; x < width(); x++)
      ss << static_cast<char>(pixel(x, y));

  os << ss.str();
}

GreyImage* GreyImage::readPGM(std::istream &is)
{
  std::stringstream ss;
  ss << is.rdbuf();

  std::string magic_number;
  ss >> magic_number;

  if (magic_number != "P5")
    throw std::runtime_error("GreyImage::readPGM : the magic number is invalid.");

  skip_line(ss);
  skip_comments(ss);

  Size width, height;
  ss >> width >> height;

  skip_line(ss);
  skip_comments(ss);

  size_t max_value;
  ss >> max_value;

  skip_line(ss);

  if (max_value != std::numeric_limits<GreyPixel>::max())
    throw std::runtime_error("GreyImage::readPGM : pixel max value is incompatible.");

  GreyImage *image = new GreyImage(width, height);

  for (size_t y = 0; y < image->height(); y++)
    for (size_t x = 0; x < image->width(); x++)
      image->pixel(x, y) = ss.get();

  return image;
}

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

  return os << static_cast<int>(value);
}
