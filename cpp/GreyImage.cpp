#include "GreyImage.hpp"
#include "Toolbox.hpp"
#include <limits>
#include <memory>

GreyImage::GreyImage(const Size width, const Size height)
    : Image<GreyPixel>(width, height) {}

GreyImage::GreyImage(const Image<GreyPixel> &image) : Image<GreyPixel>(image) {}

void GreyImage::writePGM(std::ostream &os) const {
  os << "P5\n"
     << width() << ' ' << height() << '\n'
     << std::numeric_limits<GreyPixel>::max() << '\n';

  for (size_t y = 0; y < height(); y++)
    for (size_t x = 0; x < width(); x++)
      os << static_cast<char>(pixel(x, y));
}

GreyImage *GreyImage::readPGM(std::istream &is) {
  std::string magic_number;
  is >> magic_number;

  if (magic_number != "P2" && magic_number != "P5")
    throw std::runtime_error(
        "GreyImage::readPGM : the magic number is invalid.");

  skip_line(is);
  skip_comments(is);

  int width, height;
  is >> width >> height;

  if (width < 0 || height < 0)
    throw std::runtime_error(
        "GreyImage::readPGM : the width or the height can't be negative.");

  skip_line(is);
  skip_comments(is);

  int max_value;
  is >> max_value;

  skip_line(is);

  if (max_value < 0 || max_value != std::numeric_limits<GreyPixel>::max())
    throw std::runtime_error(
        "GreyImage::readPGM : pixel max value is incompatible.");

  auto image = std::make_unique<GreyImage>(width, height);

  if (magic_number == "P2") {
    for (size_t y = 0; y < image->height(); y++)
      for (size_t x = 0; x < image->width(); x++)
        is >> image->pixel(x, y);
  } else if (magic_number == "P5") {
    for (size_t y = 0; y < image->height(); y++)
      for (size_t x = 0; x < image->width(); x++)
        image->pixel(x, y) = is.get();
  }

  return image.release();
}

GreyImage *GreyImage::simpleScale(const Size width, const Size height) const {
  std::unique_ptr<Image<GreyPixel>> imgT(
      Image<GreyPixel>::simpleScale(width, height));
  return new GreyImage(std::move(*imgT));
}

GreyImage *GreyImage::bilinearScale(const Size width, const Size height) const {
  std::unique_ptr<Image<GreyPixel>> imgT(
      Image<GreyPixel>::bilinearScale(width, height));
  return new GreyImage(std::move(*imgT));
}
