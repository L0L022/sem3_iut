#include "ColorImage.hpp"
#include "Toolbox.hpp"
#include <limits>
#include <sstream>

ColorImage::ColorImage(const Size width, const Size height)
: Image<ColorPixel>(width, height)
{}

void ColorImage::writePPM(std::ostream &os) const
{
  std::stringstream ss;
  ss << "P6\n"
     << width() << ' ' << height() << '\n'
     << std::numeric_limits<uint8_t>::max() << '\n';

  for (size_t y = 0; y < height(); y++) {
    for (size_t x = 0; x < width(); x++) {
      const ColorPixel &p = pixel(x, y);
      ss << static_cast<char>(p.red)
         << static_cast<char>(p.green)
         << static_cast<char>(p.blue);
    }
  }

  os << ss.str();
}

ColorImage* ColorImage::readPPM(std::istream &is)
{
  std::stringstream ss;
  ss << is.rdbuf();

  std::string magic_number;
  ss >> magic_number;

  if (magic_number != "P3" && magic_number != "P6")
    throw std::runtime_error("ColorImage::readPPM : the magic number is invalid.");

  skip_line(ss);
  skip_comments(ss);

  int width, height;
  ss >> width >> height;

  if (width < 0 || height < 0)
    throw std::runtime_error("ColorImage::readPPM : the width or the height can't be negative.");

  skip_line(ss);
  skip_comments(ss);

  int max_value;
  ss >> max_value;

  skip_line(ss);

  if (max_value < 0 || max_value != std::numeric_limits<uint8_t>::max())
    throw std::runtime_error("ColorImage::readPPM : pixel max value is incompatible.");

  ColorImage *image = new ColorImage(width, height);

  if (magic_number == "P3") {
    for (size_t y = 0; y < image->height(); y++)
      for (size_t x = 0; x < image->width(); x++)
        ss >> image->pixel(x, y);
  } else if (magic_number == "P6") {
    for (size_t y = 0; y < image->height(); y++) {
      for (size_t x = 0; x < image->width(); x++) {
        ColorPixel &p = image->pixel(x, y);
        p.red = ss.get();
        p.green = ss.get();
        p.blue = ss.get();
      }
    }
  }

  return image;
}

std::ostream &operator<<(std::ostream &os, const ColorPixel &pixel)
{
  return os << pixel.red << ' ' << pixel.green << ' ' << pixel.blue;
}

std::istream &operator>>(std::istream &is, ColorPixel &pixel)
{
  return is >> pixel.red >> pixel.green >> pixel.blue;
}
