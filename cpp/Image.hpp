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
	~Image();

	Image& operator=(const Image &image) = delete;

	inline Size width() const { return m_width; }
	inline Size height() const { return m_height; }

	inline Size getWidth() const { return m_width; }
	inline Size getHeight() const { return m_height; }

	Pixel& pixel(const Size x, const Size y);
	const Pixel& pixel(const Size x, const Size y) const;

	void fill(const Pixel& pixel);
	inline void clear(const Pixel& color = 0) { fill(color); }

	void hLine(const Size x, const Size y, const Size width, const Pixel& color);
	void vLine(const Size x, const Size y, const Size height, const Pixel& color);

	void rectangle(const Size x, const Size y, const Size width, const Size height, const Pixel& color);
	void fillRectangle(const Size x, const Size y, const Size width, const Size height, const Pixel& color);

private:
	inline Size pSize() const { return m_width*m_height; }

private:
	Pixel *m_pixels;
	const Size m_width, m_height;
};

std::ostream &operator<<(std::ostream &os, const Image &image);

std::ostream &operator<<(std::ostream &os, const uint8_t &pixel);

#endif
