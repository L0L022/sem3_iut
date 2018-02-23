#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>

template <typename Pixel> class Image {
public:
  typedef uint16_t Size;

  Image() = delete;
  Image(const Size width, const Size height);
  Image(const Image &image);
  Image(Image &&image);

  Image &operator=(const Image &image) = delete;

  inline Size width() const { return m_width; }
  inline Size height() const { return m_height; }

  inline Size getWidth() const { return m_width; }
  inline Size getHeight() const { return m_height; }

  Pixel &pixel(const Size x, const Size y);
  const Pixel &pixel(const Size x, const Size y) const;

  void fill(const Pixel &pixel);
  inline void clear(const Pixel &color = 0) { fill(color); }

  void hLine(const Size x, const Size y, const Size width, const Pixel &color);
  void vLine(const Size x, const Size y, const Size height, const Pixel &color);
  void line(const Size x1, const Size y1, const Size x2, const Size y2,
            const Pixel &color);

  void rectangle(const Size x, const Size y, const Size width,
                 const Size height, const Pixel &color);
  void fillRectangle(const Size x, const Size y, const Size width,
                     const Size height, const Pixel &color);

  void circle(const Size x, const Size y, const Size radius,
              const Pixel &color);
  void fillCircle(const Size x, const Size y, const Size radius,
                  const Pixel &color);

  Image *simpleScale(const Size width, const Size height) const;
  Image *bilinearScale(const Size width, const Size height) const;

private:
  inline size_t pSize() const { return m_width * m_height; }

private:
  std::unique_ptr<Pixel[]> m_pixels;
  Size m_width, m_height;
};

std::ostream &operator<<(std::ostream &os, const uint8_t &value);
std::istream &operator>>(std::istream &is, uint8_t &value);

template <typename Pixel>
Image<Pixel>::Image(const Size width, const Size height)
    : m_pixels(nullptr), m_width(width), m_height(height) {
  m_pixels = std::make_unique<Pixel[]>(pSize());
}

template <typename Pixel>
Image<Pixel>::Image(const Image &image) : Image(image.m_width, image.m_height) {
  std::memcpy(m_pixels.get(), image.m_pixels.get(), sizeof(Pixel) * pSize());
}

template <typename Pixel> Image<Pixel>::Image(Image &&image) : Image(0, 0) {
  std::swap(m_pixels, image.m_pixels);
  std::swap(m_width, image.m_width);
  std::swap(m_height, image.m_height);
}

template <typename Pixel>
Pixel &Image<Pixel>::pixel(const Size x, const Size y) {
  if (x < 0 or y < 0)
    throw std::out_of_range("Image::pixel : x or y can't be inferior to 0.");
  if (x >= m_width or y >= m_height)
    throw std::out_of_range("Image::pixel : x or y can't be superior or equal "
                            "to the width or the height of the image.");

  return m_pixels[m_width * y + x];
}

template <typename Pixel>
const Pixel &Image<Pixel>::pixel(const Size x, const Size y) const {
  if (x < 0 or y < 0)
    throw std::out_of_range(
        "Image::pixel const : the x or the y can't be inferior to 0.");
  if (x >= m_width or y >= m_height)
    throw std::out_of_range("Image::pixel const : the x or the y can't be "
                            "superior or equal to the width or the height of "
                            "the image.");

  return m_pixels[m_width * y + x];
}

template <typename Pixel> void Image<Pixel>::fill(const Pixel &pixel) {
  for (size_t i = 0; i < pSize(); ++i)
    m_pixels[i] = pixel;
}

template <typename Pixel>
void Image<Pixel>::hLine(const Size x, const Size y, const Size width,
                         const Pixel &color) {
  for (Image::Size i = 0; i < width; ++i)
    pixel(x + i, y) = color;
}

template <typename Pixel>
void Image<Pixel>::vLine(const Size x, const Size y, const Size height,
                         const Pixel &color) {
  for (Image::Size i = 0; i < height; ++i)
    pixel(x, y + i) = color;
}

template <typename Pixel>
void Image<Pixel>::line(const Size x1, const Size y1, const Size x2,
                        const Size y2, const Pixel &color) {
  Size x=x1;
  Size y=y1;
  int longX=x2-x1;
  int longY=y2-y1;

  if(longY<longX)
  { // 1er Octant
   const int c1=2*(longY-longX);
   const int c2=2*longY;
   int critere=c2-longX;
   while(x<=x2)
    {
      pixel(x, y) = color;
     if(critere>=0)
      { // changement de ligne horizontale
       y++;
       critere=critere+c1;
      }
     else
      // toujours la même ligne horizontale
      critere=critere+c2;
     x++; // ligne suivante, et recommence
    }
  }
  else
  { // 2eme Octant
   const int c1=2*(longX-longY);
   const int c2=2*longX;
   int critere=c2-longY;
   while(y<=y2)
    {
      pixel(x, y) = color;
     if(critere>=0)
      { // changement de ligne verticale
       x++;
       critere=critere+c1;
      }
     else
      // toujours la même ligne verticale
      critere=critere+c2;
     y++; // ligne suivante, et recommence
    }
  }
}

template <typename Pixel>
void Image<Pixel>::rectangle(const Size x, const Size y, const Size width,
                             const Size height, const Pixel &color) {
  hLine(x, y, width, color);
  vLine(x, y, height, color);
  hLine(x, y + std::max(0, height - 1), width, color);
  vLine(x + std::max(0, width - 1), y, height, color);
}

template <typename Pixel>
void Image<Pixel>::fillRectangle(const Size x, const Size y, const Size width,
                                 const Size height, const Pixel &color) {
  for (Image::Size i = 0; i < height; ++i)
    hLine(x, y + i, width, color);
}

template <typename Pixel>
void Image<Pixel>::circle(const Size x, const Size y, const Size radius,
                          const Pixel &color) {
  // merci Eric Andres
  Size _x = 0, _y = radius, d = radius - 1;
  while (_y >= _x) {
    pixel(x + _x, y + _y) = color; // 4
    pixel(x + _y, y + _x) = color; // 3
    pixel(x - _x, y + _y) = color; // 5
    pixel(x - _y, y + _x) = color; // 6
    pixel(x + _x, y - _y) = color; // 1
    pixel(x + _y, y - _x) = color; // 2
    pixel(x - _x, y - _y) = color; // 8
    pixel(x - _y, y - _x) = color; // 7

    if (d >= 2 * _x) {
      d = d - 2 * _x - 1;
      _x = _x + 1;
    } else if (d < 2 * (radius - _y)) {
      d = d + 2 * _y - 1;
      _y = _y - 1;
    } else {
      d = d + 2 * (_y - _x - 1);
      _y = _y - 1;
      _x = _x + 1;
    }
  }
}

template <typename Pixel>
void Image<Pixel>::fillCircle(const Size x, const Size y, const Size radius,
                              const Pixel &color) {
  // merci Eric Andres
  Size _x = 0, _y = radius, d = radius - 1;
  while (_y >= _x) {
    hLine(x - _x, y - _y, 2 * _x + 1, color);
    hLine(x - _y, y - _x, 2 * _y + 1, color);
    hLine(x - _y, y + _x, 2 * _y + 1, color);
    hLine(x - _x, y + _y, 2 * _x + 1, color);

    if (d >= 2 * _x) {
      d = d - 2 * _x - 1;
      _x = _x + 1;
    } else if (d < 2 * (radius - _y)) {
      d = d + 2 * _y - 1;
      _y = _y - 1;
    } else {
      d = d + 2 * (_y - _x - 1);
      _y = _y - 1;
      _x = _x + 1;
    }
  }
}

template <typename Pixel>
Image<Pixel> *Image<Pixel>::simpleScale(const Size width,
                                        const Size height) const {
  if (width < 1 and height < 1)
    throw std::runtime_error("");

  auto img = std::make_unique<Image<Pixel>>(width, height);

  for (Size y = 0; y < height; ++y)
    for (Size x = 0; x < width; ++x)
      img->pixel(x, y) =
          pixel(x / static_cast<double>(width) * this->width(),
                y / static_cast<double>(height) * this->height());

  return img.release();
}

template <typename Pixel>
Image<Pixel> *Image<Pixel>::bilinearScale(const Size width,
                                          const Size height) const {
  auto img = std::make_unique<Image<Pixel>>(width, height);

  for (Size y = 0; y < height; ++y) {
    for (Size x = 0; x < width; ++x) {
      double px = x / static_cast<double>(width) * this->width(),
             py = y / static_cast<double>(height) * this->height();
      Size x1 = px, y1 = py;
      Size x2 = std::min(x1 + 1, this->width() - 1),
           y2 = std::min(y1 + 1, this->height() - 1);
      double dx = px - x1, dy = py - y1;
      img->pixel(x, y) =
          (pixel(x1, y1) * (1.0 - dy) + pixel(x1, y2) * dy) * (1.0 - dx) +
          (pixel(x2, y1) * (1.0 - dy) + pixel(x2, y2) * dy) * dx;
    }
  }

  return img.release();
}

template <typename Pixel>
std::ostream &operator<<(std::ostream &os, const Image<Pixel> &image) {
  for (typename Image<Pixel>::Size y = 0; y < image.height(); ++y) {
    for (typename Image<Pixel>::Size x = 0; x < image.width(); ++x) {
      os << image.pixel(x, y) << '\t';
    }
    os << std::endl;
  }

  return os;
}

#endif
