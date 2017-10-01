#include "ColorImage.hpp"
#include "Toolbox.hpp"
#include <limits>
#include <sstream>
#include <cstdlib>

extern "C" {
  #include <jpeglib.h>
}

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

void ColorImage::writeJPEG(std::ostream &os, int quality) const
{
  struct jpeg_compress_struct jpegInfo;
  struct jpeg_error_mgr jpegError;

  JSAMPLE * jsamples = new JSAMPLE[width()*3];
  JSAMPROW jsamplesRow[1];
  jsamplesRow[0] = jsamples;

  jpegInfo.err = jpeg_std_error(&jpegError);
  jpeg_create_compress(&jpegInfo);

  unsigned char *pixels = nullptr;
  unsigned long pixelsSize = 0;
  jpeg_mem_dest(&jpegInfo, &pixels, &pixelsSize);

  jpegInfo.image_width = width();
  jpegInfo.image_height = height();
  jpegInfo.input_components = 3;
  jpegInfo.in_color_space = JCS_RGB;

  jpeg_set_defaults(&jpegInfo);
  jpeg_set_quality(&jpegInfo, quality, TRUE);

  jpeg_start_compress(&jpegInfo, TRUE);
  while (jpegInfo.next_scanline < jpegInfo.image_height) {
     for (size_t x = 0; x < width(); x++) {
       const ColorPixel &p = pixel(x, jpegInfo.next_scanline);
       jsamples[x*3] = static_cast<char>(p.red);
       jsamples[x*3+1] = static_cast<char>(p.green);
       jsamples[x*3+2] = static_cast<char>(p.blue);
     }
    jpeg_write_scanlines(&jpegInfo, jsamplesRow, 1);
  }

  jpeg_finish_compress(&jpegInfo);
  jpeg_destroy_compress(&jpegInfo);
  delete[] jsamples;

  os.write(reinterpret_cast<const char*>(pixels), pixelsSize);
  free(pixels);
}

ColorImage* ColorImage::readJPEG(std::istream &is)
{

}

std::ostream &operator<<(std::ostream &os, const ColorPixel &pixel)
{
  return os << pixel.red << ' ' << pixel.green << ' ' << pixel.blue;
}

std::istream &operator>>(std::istream &is, ColorPixel &pixel)
{
  return is >> pixel.red >> pixel.green >> pixel.blue;
}
