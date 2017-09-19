#include "Image.hpp"
#include <cstring>
#include <string>

Image::Image(const Size width, const Size height)
: m_pixels(nullptr),
  m_width(width),
  m_height(height)
{
	m_pixels = new Pixel[m_width*m_height];
	std::memset(m_pixels, 0, m_width*m_height);
}

Image::Image(const Image &image)
: Image(image.m_width, image.m_height)
{
	std::memcpy(m_pixels, image.m_pixels, m_width*m_height);
}

std::ostream &operator<<(std::ostream &os, const Image &image)
{
	for (Image::Size y = 0; y < image.height(); ++y) {
		for (Image::Size x = 0; x < image.width(); ++x) {
			os << image.pixel(x, y) << ' ';
		}
		os << std::endl;
	}

	return os;
}
