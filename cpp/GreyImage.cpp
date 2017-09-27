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

  if (magic_number != "P2" && magic_number != "P5")
    throw std::runtime_error("GreyImage::readPGM : the magic number is invalid.");

  skip_line(ss);
  skip_comments(ss);

  int width, height;
  ss >> width >> height;

  if (width < 0 || height < 0)
    throw std::runtime_error("GreyImage::readPGM : the width or the height can't be negative.");

  skip_line(ss);
  skip_comments(ss);

  int max_value;
  ss >> max_value;

  skip_line(ss);

  if (max_value < 0 || max_value != std::numeric_limits<GreyPixel>::max())
    throw std::runtime_error("GreyImage::readPGM : pixel max value is incompatible.");

  GreyImage *image = new GreyImage(width, height);

  if (magic_number == "P2") {
    for (size_t y = 0; y < image->height(); y++)
      for (size_t x = 0; x < image->width(); x++)
        ss >> image->pixel(x, y);
  } else if (magic_number == "P5") {
    for (size_t y = 0; y < image->height(); y++)
      for (size_t x = 0; x < image->width(); x++)
        image->pixel(x, y) = ss.get();
  }

  return image;
}
