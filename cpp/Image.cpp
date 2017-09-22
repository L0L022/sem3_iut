#include "Image.hpp"
#include <cstring>
#include <string>
#include <stdexcept>
#include <algorithm>

Image::Image(const Size width, const Size height)
: m_pixels(nullptr),
  m_width(width),
  m_height(height)
{
	m_pixels = new Pixel[pSize()];
}

Image::Image(const Image &image)
: Image(image.m_width, image.m_height)
{
	std::memcpy(m_pixels, image.m_pixels, sizeof(Pixel) * pSize());
}

Image::~Image()
{
  delete[] m_pixels;
}

Image::Pixel& Image::pixel(const Size x, const Size y)
{
  if (x < 0 or y < 0)
    throw std::out_of_range("Image::pixel : x or y can't be inferior to 0.");
  if (x >= m_width or y >= m_height)
    throw std::out_of_range("Image::pixel : x or y can't be superior or equal to the width or the height of the image.");

  return m_pixels[m_width*y+x];
}

const Image::Pixel &Image::pixel(const Size x, const Size y) const
{
  if (x < 0 or y < 0)
    throw std::out_of_range("Image::pixel const : the x or the y can't be inferior to 0.");
  if (x >= m_width or y >= m_height)
    throw std::out_of_range("Image::pixel const : the x or the y can't be superior or equal to the width or the height of the image.");

  return m_pixels[m_width*y+x];
}

void Image::fill(const Pixel& pixel)
{
  for (Size i = 0; i < pSize(); ++i)
    m_pixels[i] = pixel;
}

void Image::hLine(const Size x, const Size y, const Size width, const Pixel& color)
{
  for (Image::Size i = 0; i < width; ++i)
    pixel(x + i, y) = color;
}

void Image::vLine(const Size x, const Size y, const Size height, const Pixel& color)
{
  for (Image::Size i = 0; i < height; ++i)
    pixel(x, y + i) = color;
}

void Image::rectangle(const Size x, const Size y, const Size width, const Size height, const Pixel& color)
{
  hLine(x, y, width, color);
  vLine(x, y, height, color);
  hLine(x, y + std::max(0, height - 1), width, color);
  vLine(x + std::max(0, width - 1), y, height, color);
}

void Image::fillRectangle(const Size x, const Size y, const Size width, const Size height, const Pixel& color)
{
  for (Image::Size i = 0; i < height; ++i)
    hLine(x, y + i, width, color);
}

std::ostream &operator<<(std::ostream &os, const Image &image)
{
	for (Image::Size y = 0; y < image.height(); ++y) {
		for (Image::Size x = 0; x < image.width(); ++x) {
			os << image.pixel(x, y) << '\t';
		}
		os << std::endl;
	}

	return os;
}

std::ostream &operator<<(std::ostream &os, const uint8_t &pixel)
{
  return os << static_cast<int>(pixel);
}
