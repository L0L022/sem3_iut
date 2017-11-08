#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstdint>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <algorithm>

template<typename Pixel>
class Image
{
public:
	typedef uint16_t Size;

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

	void circle(const Size x, const Size y, const Size radius, const Pixel& color);
	void fillCircle(const Size x, const Size y, const Size radius, const Pixel& color);

	void line(const Size x1, const Size y1, const Size x2, const Size y2, const Pixel& color);

private:
	inline size_t pSize() const { return m_width*m_height; }

private:
	Pixel *m_pixels;
	const Size m_width, m_height;
};

std::ostream &operator<<(std::ostream &os, const uint8_t &value);
std::istream &operator>>(std::istream &is, uint8_t &value);

template<typename Pixel>
Image<Pixel>::Image(const Size width, const Size height)
: m_pixels(nullptr),
  m_width(width),
  m_height(height)
{
	m_pixels = new Pixel[pSize()];
}

template<typename Pixel>
Image<Pixel>::Image(const Image &image)
: Image(image.m_width, image.m_height)
{
	std::memcpy(m_pixels, image.m_pixels, sizeof(Pixel) * pSize());
}

template<typename Pixel>
Image<Pixel>::~Image()
{
  delete[] m_pixels;
}

template<typename Pixel>
Pixel& Image<Pixel>::pixel(const Size x, const Size y)
{
  if (x < 0 or y < 0)
    throw std::out_of_range("Image::pixel : x or y can't be inferior to 0.");
  if (x >= m_width or y >= m_height)
    throw std::out_of_range("Image::pixel : x or y can't be superior or equal to the width or the height of the image.");

  return m_pixels[m_width*y+x];
}

template<typename Pixel>
const Pixel &Image<Pixel>::pixel(const Size x, const Size y) const
{
  if (x < 0 or y < 0)
    throw std::out_of_range("Image::pixel const : the x or the y can't be inferior to 0.");
  if (x >= m_width or y >= m_height)
    throw std::out_of_range("Image::pixel const : the x or the y can't be superior or equal to the width or the height of the image.");

  return m_pixels[m_width*y+x];
}

template<typename Pixel>
void Image<Pixel>::fill(const Pixel& pixel)
{
  for (size_t i = 0; i < pSize(); ++i)
    m_pixels[i] = pixel;
}

template<typename Pixel>
void Image<Pixel>::hLine(const Size x, const Size y, const Size width, const Pixel& color)
{
  for (Image::Size i = 0; i < width; ++i)
    pixel(x + i, y) = color;
}

template<typename Pixel>
void Image<Pixel>::vLine(const Size x, const Size y, const Size height, const Pixel& color)
{
  for (Image::Size i = 0; i < height; ++i)
    pixel(x, y + i) = color;
}

template<typename Pixel>
void Image<Pixel>::rectangle(const Size x, const Size y, const Size width, const Size height, const Pixel& color)
{
  hLine(x, y, width, color);
  vLine(x, y, height, color);
  hLine(x, y + std::max(0, height - 1), width, color);
  vLine(x + std::max(0, width - 1), y, height, color);
}

template<typename Pixel>
void Image<Pixel>::fillRectangle(const Size x, const Size y, const Size width, const Size height, const Pixel& color)
{
  for (Image::Size i = 0; i < height; ++i)
    hLine(x, y + i, width, color);
}

template<typename Pixel>
void Image<Pixel>::circle(const Size x, const Size y, const Size radius, const Pixel& color)
{
	//merci Eric Andres
	Size _x = 0, _y = radius, d = radius - 1;
	while (_y >= _x) {
		pixel( x + _x , y + _y ) = color; //4
		pixel( x + _y , y + _x ) = color; //3
		pixel( x - _x , y + _y ) = color; //5
		pixel( x - _y , y + _x ) = color; //6
		pixel( x + _x , y - _y ) = color; //1
		pixel( x + _y , y - _x ) = color; //2
		pixel( x - _x , y - _y ) = color; //8
		pixel( x - _y , y - _x ) = color; //7

		if (d >= 2*_x) {
			d = d - 2*_x-1;
			_x = _x + 1;
		} else if (d < 2*(radius-_y)) {
			d = d + 2*_y-1;
			_y = _y - 1;
		} else {
			d = d + 2 * (_y - _x - 1);
			_y = _y - 1;
			_x = _x + 1;
		}
	}
}

template<typename Pixel>
void Image<Pixel>::fillCircle(const Size x, const Size y, const Size radius, const Pixel& color)
{
	//merci Eric Andres
	Size _x = 0, _y = radius, d = radius - 1;
	while (_y >= _x) {
		// hLine( x - _x , y - _y , (x + _x) - (x - _x) + 1, color);
		// hLine( x - _y , y - _x , (x + _y) - (x - _y) + 1, color);
		// hLine( x - _y , y + _x , (x + _y) - (x - _y) + 1, color);
		// hLine( x - _x , y + _y , (x + _x) - (x - _x) + 1, color);
		hLine( x - _x , y - _y , 2 * _x + 1, color);
		hLine( x - _y , y - _x , 2 * _y + 1, color);
		hLine( x - _y , y + _x , 2 * _y + 1, color);
		hLine( x - _x , y + _y , 2 * _x + 1, color);

		if (d >= 2*_x) {
			d = d - 2*_x-1;
			_x = _x + 1;
		} else if (d < 2*(radius-_y)) {
			d = d + 2*_y-1;
			_y = _y - 1;
		} else {
			d = d + 2 * (_y - _x - 1);
			_y = _y - 1;
			_x = _x + 1;
		}
	}
}

template<typename Pixel>
void Image<Pixel>::line(const Size x1, const Size y1, const Size x2, const Size y2, const Pixel& color)
{
	size_t dx = 0, dy = 0;
	if ((dx = x2 - x1) != 0) {
		if (dx > 0) {
			if ((dy = y2 - y1) != 0) {
				if (dy > 0) {
					if (dx >= dy) {
						size_t e = dx;
						dx *= 2;
						dy *= 2;
						while (true) {
							pixel(x1, y1) = color;
							if (++x1 == x2)
								break;
							if ((e -= dy) < 0) {
								++y1;
								e += dx;
							}
						}
					} else {
						size_t e = dy;
						dy *= 2;
						dx *= 2;
						while (true) {
							pixel(x1, y1) = color;
							if (++y1 == y2)
								break;
							if ((e -= dx) < 0) {
								++x1;
								e += dy;
							}
						}
					}

				}
			}
		}
	}
}

template<typename Pixel>
std::ostream &operator<<(std::ostream &os, const Image<Pixel> &image)
{
	for (typename Image<Pixel>::Size y = 0; y < image.height(); ++y) {
		for (typename Image<Pixel>::Size x = 0; x < image.width(); ++x) {
			os << image.pixel(x, y) << '\t';
		}
		os << std::endl;
	}

	return os;
}

#endif
