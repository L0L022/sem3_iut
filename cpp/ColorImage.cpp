#include "ColorImage.hpp"
#include "Toolbox.hpp"
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

extern "C" {
#include <jpeglib.h>
}

ColorImage::ColorImage(const Size width, const Size height)
    : Image<ColorPixel>(width, height) {}

ColorImage::ColorImage(const Image<ColorPixel> &image)
    : Image<ColorPixel>(image) {}

ColorImage *ColorImage::simpleScale(const Size width, const Size height) const {
  std::unique_ptr<Image<ColorPixel>> imgT(
      Image<ColorPixel>::simpleScale(width, height));
  return new ColorImage(std::move(*imgT));
}

ColorImage *ColorImage::bilinearScale(const Size width,
                                      const Size height) const {
  std::unique_ptr<Image<ColorPixel>> imgT(
      Image<ColorPixel>::bilinearScale(width, height));
  return new ColorImage(std::move(*imgT));
}

void ColorImage::writePPM(std::ostream &os) const {
  os << "P6\n"
     << width() << ' ' << height() << '\n'
     << std::numeric_limits<uint8_t>::max() << '\n';

  for (size_t y = 0; y < height(); y++) {
    for (size_t x = 0; x < width(); x++) {
      const ColorPixel &p = pixel(x, y);
      os << static_cast<char>(p.red) << static_cast<char>(p.green)
         << static_cast<char>(p.blue);
    }
  }
}

ColorImage *ColorImage::readPPM(std::istream &is) {
  std::string magic_number;
  is >> magic_number;

  if (magic_number != "P3" && magic_number != "P6")
    throw std::runtime_error(
        "ColorImage::readPPM : the magic number is invalid.");

  skip_line(is);
  skip_comments(is);

  int width, height;
  is >> width >> height;

  if (width < 0 || height < 0)
    throw std::runtime_error(
        "ColorImage::readPPM : the width or the height can't be negative.");

  skip_line(is);
  skip_comments(is);

  int max_value;
  is >> max_value;

  skip_line(is);

  if (max_value < 0 || max_value != std::numeric_limits<uint8_t>::max())
    throw std::runtime_error(
        "ColorImage::readPPM : pixel max value is incompatible.");

  auto image = std::make_unique<ColorImage>(width, height);

  if (magic_number == "P3") {
    for (size_t y = 0; y < image->height(); y++)
      for (size_t x = 0; x < image->width(); x++)
        is >> image->pixel(x, y);
  } else if (magic_number == "P6") {
    for (size_t y = 0; y < image->height(); y++) {
      for (size_t x = 0; x < image->width(); x++) {
        ColorPixel &p = image->pixel(x, y);
        p.red = is.get();
        p.green = is.get();
        p.blue = is.get();
      }
    }
  }

  return image.release();
}

METHODDEF(void)
jpeg_error(j_common_ptr cinfo) {
  char error_message[500] = "JPEG error : ";
  (*cinfo->err->format_message)(cinfo,
                                error_message + std::strlen(error_message));
  jpeg_destroy(cinfo);
  throw std::runtime_error(error_message);
}

void ColorImage::writeJPEG(std::ostream &os, unsigned int quality) const {
  struct jpeg_compress_struct jpegInfo;
  struct jpeg_error_mgr jpegError;

  auto jsamples = std::make_unique<JSAMPLE[]>(width() * 3);
  JSAMPROW jsamplesRow[1];
  jsamplesRow[0] = jsamples.get();

  jpegInfo.err = jpeg_std_error(&jpegError);
  jpegError.error_exit = jpeg_error;
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
      jsamples[x * 3] = static_cast<char>(p.red);
      jsamples[x * 3 + 1] = static_cast<char>(p.green);
      jsamples[x * 3 + 2] = static_cast<char>(p.blue);
    }
    jpeg_write_scanlines(&jpegInfo, jsamplesRow, 1);
  }

  jpeg_finish_compress(&jpegInfo);
  jpeg_destroy_compress(&jpegInfo);

  os.write(reinterpret_cast<const char *>(pixels), pixelsSize);
  free(pixels);
}

void ColorImage::writeJPEG(const std::string &fileName,
                           unsigned int quality) const {
  std::ofstream file(fileName, std::ios::binary | std::ios::out);
  if (file.is_open())
    writeJPEG(file, quality);
  else
    throw std::runtime_error("Can't open file");
}

void ColorImage::writeJPEG(const char *fileName, unsigned int quality) const {
  writeJPEG(fileName);
}

ColorImage *ColorImage::readJPEG(std::istream &is) {
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jpegError;

  cinfo.err = jpeg_std_error(&jpegError);
  jpegError.error_exit = jpeg_error;

  std::stringstream ss;
  ss << is.rdbuf();
  std::string imageSource(ss.str());

  jpeg_create_decompress(&cinfo);
  jpeg_mem_src(&cinfo,
               reinterpret_cast<const unsigned char *>(imageSource.c_str()),
               imageSource.size());
  jpeg_read_header(&cinfo, TRUE);
  jpeg_start_decompress(&cinfo);

  int row_stride = cinfo.output_width * cinfo.output_components;
  JSAMPARRAY buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo,
                                                 JPOOL_IMAGE, row_stride, 1);
  auto finalImage =
      std::make_unique<ColorImage>(cinfo.output_width, cinfo.output_height);

  while (cinfo.output_scanline < cinfo.output_height) {
    jpeg_read_scanlines(&cinfo, buffer, 1);
    for (size_t x = 0; x < finalImage->width(); x++) {
      ColorPixel &p = finalImage->pixel(x, cinfo.output_scanline - 1);
      p.red = buffer[0][x * 3];
      p.green = buffer[0][x * 3 + 1];
      p.blue = buffer[0][x * 3 + 2];
    }
  }

  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);

  return finalImage.release();
}

ColorImage *ColorImage::readJPEG(const std::string &fileName) {
  std::ifstream file(fileName, std::ios::binary);
  if (file.is_open())
    return readJPEG(file);
  else
    throw std::runtime_error("Can't open file");
}

ColorImage *ColorImage::readJPEG(const char *fileName) {
  return readJPEG(fileName);
}

class targa_info {
public:
  uint8_t identification_length;
  uint8_t color_map_type;
  uint8_t type;

  // Color Map Specification
  uint16_t color_map_first_entry_index;
  uint16_t color_map_length;
  uint8_t color_map_entry_size;

  // Image Specification
  uint16_t x_origin;
  uint16_t y_origin;
  uint16_t width;
  uint16_t height;
  uint8_t pixel_depth;
  uint8_t description;

  uint8_t *identification;
  uint8_t *color_map_data;
  uint8_t *data;

  size_t color_map_data_length;
  size_t data_length;

private:
  std::unique_ptr<uint8_t[]> _identification;
  std::unique_ptr<uint8_t[]> _color_map_data;
  std::unique_ptr<uint8_t[]> _data;

public:
  targa_info()
      : identification_length(0), color_map_type(0), type(0),
        color_map_first_entry_index(0), color_map_length(0),
        color_map_entry_size(0), x_origin(0), y_origin(0), width(0), height(0),
        pixel_depth(0), description(0), identification(nullptr),
        color_map_data(nullptr), data(nullptr), color_map_data_length(0),
        data_length(0) {}

  void update() {
    update_length();
    update_memory();
  }

  void update_length() {
    color_map_data_length = color_map_length * color_map_entry_size / 8;
    data_length = width * height * pixel_depth / 8;
  }

  void update_memory() {
    _identification = std::make_unique<uint8_t[]>(identification_length);
    identification = _identification.get();

    _color_map_data = std::make_unique<uint8_t[]>(color_map_data_length);
    color_map_data = _color_map_data.get();

    _data = std::make_unique<uint8_t[]>(data_length);
    data = _data.get();
  }
};

std::ostream &operator<<(std::ostream &os, const targa_info &i) {
  os.write(reinterpret_cast<const char *>(&i.identification_length), 1);
  os.write(reinterpret_cast<const char *>(&i.color_map_type), 1);
  os.write(reinterpret_cast<const char *>(&i.type), 1);
  os.write(reinterpret_cast<const char *>(&i.color_map_first_entry_index), 2);
  os.write(reinterpret_cast<const char *>(&i.color_map_length), 2);
  os.write(reinterpret_cast<const char *>(&i.color_map_entry_size), 1);
  os.write(reinterpret_cast<const char *>(&i.x_origin), 2);
  os.write(reinterpret_cast<const char *>(&i.y_origin), 2);
  os.write(reinterpret_cast<const char *>(&i.width), 2);
  os.write(reinterpret_cast<const char *>(&i.height), 2);
  os.write(reinterpret_cast<const char *>(&i.pixel_depth), 1);
  os.write(reinterpret_cast<const char *>(&i.description), 1);

  if (i.identification)
    os.write(reinterpret_cast<const char *>(i.identification),
             i.identification_length);
  if (i.color_map_data)
    os.write(reinterpret_cast<const char *>(i.color_map_data),
             i.color_map_data_length);
  if (i.data)
    os.write(reinterpret_cast<const char *>(i.data), i.data_length);
  else
    throw std::runtime_error("No image data");

  return os;
}

std::istream &operator>>(std::istream &is, targa_info &i) {
  is.read(reinterpret_cast<char *>(&i.identification_length), 1);
  is.read(reinterpret_cast<char *>(&i.color_map_type), 1);
  is.read(reinterpret_cast<char *>(&i.type), 1);
  is.read(reinterpret_cast<char *>(&i.color_map_first_entry_index), 2);
  is.read(reinterpret_cast<char *>(&i.color_map_length), 2);
  is.read(reinterpret_cast<char *>(&i.color_map_entry_size), 1);
  is.read(reinterpret_cast<char *>(&i.x_origin), 2);
  is.read(reinterpret_cast<char *>(&i.y_origin), 2);
  is.read(reinterpret_cast<char *>(&i.width), 2);
  is.read(reinterpret_cast<char *>(&i.height), 2);
  is.read(reinterpret_cast<char *>(&i.pixel_depth), 1);
  is.read(reinterpret_cast<char *>(&i.description), 1);

  i.update();

  if (i.identification)
    is.read(reinterpret_cast<char *>(i.identification),
            i.identification_length);
  if (i.color_map_data)
    is.read(reinterpret_cast<char *>(i.color_map_data),
            i.color_map_data_length);
  if (i.data)
    is.read(reinterpret_cast<char *>(i.data), i.data_length);
  else
    throw std::runtime_error("No image data");

  return is;
}

class targa_packet {
public:
  const size_t MAX_COUNT = 128;
  virtual uint8_t *write(uint8_t *data) const = 0;
  virtual size_t size() const = 0;
};

class targa_packet_raw : public targa_packet {
public:
  std::vector<ColorPixel> pixels;

  targa_packet_raw(const std::vector<ColorPixel> &pixels) : pixels(pixels) {}

  uint8_t *write(uint8_t *data) const {
    for (size_t offset = 0; offset < pixels.size(); offset += 128) {
      uint8_t length = std::min(pixels.size() - offset, 128ul);
      *data++ = length - 1;
      for (size_t i = 0; i < length; ++i) {
        *data++ = pixels[offset + i].blue;
        *data++ = pixels[offset + i].green;
        *data++ = pixels[offset + i].red;
      }
    }
    return data;
  }

  size_t size() const {
    return pixels.size() == 0
               ? 0
               : 1 + ((pixels.size() - 1) / MAX_COUNT) + pixels.size() * 3;
  }
};

class targa_packet_rle : public targa_packet {
public:
  ColorPixel pixel;
  size_t count;

  targa_packet_rle() : count(0) {}
  targa_packet_rle(const ColorPixel &pixel, const size_t count)
      : pixel(pixel), count(count) {}

  uint8_t *write(uint8_t *data) const {
    for (size_t offset = 0; offset < count; offset += 128) {
      uint8_t length = std::min(count - offset, 128ul);
      *data++ = 0b10000000 | (length - 1);
      *data++ = pixel.blue;
      *data++ = pixel.green;
      *data++ = pixel.red;
    }
    return data;
  }

  size_t size() const {
    if (count == 0) {
      return 0;
    } else {
      size_t nb_header = 1 + ((count - 1) / MAX_COUNT);
      return nb_header + nb_header * 3;
    }
  }
};

void ColorImage::writeTGA(std::ostream &os, bool rle) const {
  targa_info i;
  i.width = width();
  i.height = height();
  i.description = 0b00100000;
  i.pixel_depth = 3 * 8;

  if (rle) {
    i.type = 10;

    std::vector<ColorPixel> pixels;
    size_t count_same_color = 0;
    std::vector<std::unique_ptr<targa_packet>> packets;

    for (size_t y = 0; y < height(); y++) {
      for (size_t x = 0; x < width(); x++) {
        auto &p = pixel(x, y);
        if (pixels.empty()) {
          pixels.push_back(p);
        } else {
          if (p == pixels.back()) {
            if (pixels.size() > 1) {
              pixels.pop_back();
              packets.push_back(std::make_unique<targa_packet_raw>(pixels));
              pixels.clear();
              pixels.push_back(p);
            }
            if (count_same_color == 0)
              count_same_color = 1;
            ++count_same_color;
          } else {
            if (count_same_color > 0) {
              packets.push_back(std::make_unique<targa_packet_rle>(
                  pixels.back(), count_same_color));
              pixels.back() = p;
              count_same_color = 0;
            } else {
              pixels.push_back(p);
            }
          }
        }
      }
    }
    if (not pixels.empty()) {
      if (count_same_color > 0)
        packets.push_back(std::make_unique<targa_packet_rle>(pixels.back(),
                                                             count_same_color));
      else
        packets.push_back(std::make_unique<targa_packet_raw>(pixels));
    }

    i.data_length = 0;
    for (const auto &p : packets)
      i.data_length += p->size();

    i.update_memory();

    uint8_t *data = i.data;
    for (const auto &p : packets)
      data = p->write(data);

  } else {
    i.type = 2;
    i.update();

    for (size_t y = 0; y < height(); y++) {
      for (size_t x = 0; x < width(); x++) {
        auto &p = pixel(x, y);
        uint8_t *p_data = i.data + (i.width * y + x) * 3;
        *p_data++ = p.blue;
        *p_data++ = p.green;
        *p_data = p.red;
      }
    }
  }

  os << i;
}

ColorImage *ColorImage::readTGA(std::istream &is) {
  targa_info i;
  is >> i;

  auto image = std::make_unique<ColorImage>(i.width, i.height);

  if (i.type == 1) {
    if (i.pixel_depth == 8 /*and i.description == 0b00100000*/ and
        i.color_map_entry_size == 24) {
      for (size_t y = 0; y < image->height(); y++) {
        for (size_t x = 0; x < image->width(); x++) {
          auto &p = i.description == 0b00100000 ? image->pixel(x, y) : image->pixel(x, image->height() - y);
          uint8_t indice = i.data[i.width * y + x];
          uint8_t *p_data = i.color_map_data + indice * 3;
          p.blue = *p_data++;
          p.green = *p_data++;
          p.red = *p_data;
        }
      }
    } else {
      throw std::runtime_error("Unsupported tga type 1");
    }
  } else if (i.type == 2) {
    if (i.pixel_depth == 3 * 8 /*and i.description == 0b00100000*/) {
      for (size_t y = 0; y < image->height(); y++) {
        for (size_t x = 0; x < image->width(); x++) {
          auto &p = i.description == 0b00100000 ? image->pixel(x, y) : image->pixel(x, image->height() - y);
          uint8_t *p_data = i.data + (i.width * y + x) * 3;
          p.blue = *p_data++;
          p.green = *p_data++;
          p.red = *p_data;
        }
      }
    } else {
      throw std::runtime_error("Unsupported tga type 2");
    }
  } else {
    throw std::runtime_error("Unknown tga type");
  }

  return image.release();
}

void reverse_bytes(char *ptr, const size_t length) {
  for (size_t i = 0; i < length / 2; ++i)
    std::swap(ptr[i], ptr[length - i - 1]);
}

ColorImage *ColorImage::readMaison2(std::istream &is) {
  char magic_number[7];
  uint8_t comment_length;
  uint16_t height;
  uint16_t width;
  std::unique_ptr<uint8_t[]> comment;
  std::unique_ptr<uint8_t[]> data;
  size_t data_length;

  is.read(magic_number, 7);
  is.read(reinterpret_cast<char *>(&comment_length), 1);
  is.read(reinterpret_cast<char *>(&height), 2);
  is.read(reinterpret_cast<char *>(&width), 2);
  reverse_bytes(reinterpret_cast<char *>(&height), 2);
  reverse_bytes(reinterpret_cast<char *>(&width), 2);

  comment = std::make_unique<uint8_t[]>(comment_length);
  data_length = width * height * 3;
  data = std::make_unique<uint8_t[]>(data_length);

  is.read(reinterpret_cast<char *>(comment.get()), comment_length);
  is.read(reinterpret_cast<char *>(data.get()), data_length);

  if (strncmp(magic_number, "Maison2", 7) != 0)
    throw std::runtime_error("Wrong magic number");

  auto image = std::make_unique<ColorImage>(width, height);

  for (size_t y = 0; y < image->height(); y++) {
    for (size_t x = 0; x < image->width(); x++) {
      auto &p = image->pixel(x, y);
      uint8_t *p_data = data.get() + (width * y + x);
      p.green = *p_data;
      p.blue = *(p_data +=(width * height));
      p.red = *(p_data +=(width * height));
    }
  }

  std::cout.write(reinterpret_cast<char *>(comment.get()), comment_length);
  std::cout << '\n';

  return image.release();
}

ColorImage *ColorImage::anaglyphe() const {
  auto image = std::make_unique<ColorImage>(width() / 2, height());

  for (size_t y = 0; y < image->height(); y++) {
    for (size_t x = 0; x < image->width(); x++) {
      ColorPixel left = pixel(x + width()/2, y), right = pixel(x, y);
      image->pixel(x, y) = ColorPixel(left.red, right.green, right.blue);
    }
  }

  return image.release();
}

std::ostream &operator<<(std::ostream &os, const ColorPixel &pixel) {
  return os << pixel.red << ' ' << pixel.green << ' ' << pixel.blue;
}

std::istream &operator>>(std::istream &is, ColorPixel &pixel) {
  return is >> pixel.red >> pixel.green >> pixel.blue;
}
