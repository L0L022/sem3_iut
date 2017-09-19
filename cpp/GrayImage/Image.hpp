#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstdint>
#include <iostream>

class Image
{
public:
	typedef uint16_t Size;
	typedef uint8_t Pixel;

	Image() = delete;
	Image(const Size width, const Size height);
	Image(const Image &image);

	Image operator=(const Image &image) = delete;

	inline Size width() const { return m_width; }
	inline Size height() const { return m_height; }

	inline Pixel &pixel(const Size width, const Size height) { return m_pixels[m_width*width+height]; }
	inline const Pixel &pixel(const Size width, const Size height) const { return m_pixels[m_width*width+height]; }



private:
	Pixel *m_pixels;
	Size m_width, m_height;
};

std::ostream &operator<<(std::ostream &os, const Image &image);

#endif
