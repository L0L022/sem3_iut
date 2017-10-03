#include "ColorImage.hpp"
#include "Toolbox.hpp"
#include <limits>
#include <sstream>
#include <cstdlib>
#include <string>

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
  /* This struct contains the JPEG decompression parameters and pointers to
   * working space (which is allocated as needed by the JPEG library).
   */
  struct jpeg_decompress_struct cinfo;
  /* We use our private extension JPEG error handler.
   * Note that this struct must live as long as the main JPEG parameter
   * struct, to avoid dangling-pointer problems.
   */
   struct jpeg_error_mgr jpegError;
  // struct my_error_mgr jerr;
  /* More stuff */
  std::stringstream ss;
  ss << is.rdbuf();
  std::string imageSource(ss.str());

  JSAMPARRAY buffer;		/* Output row buffer */
  int row_stride;		/* physical row width in output buffer */

  /* In this example we want to open the input file before doing anything else,
   * so that the setjmp() error recovery below can assume the file is open.
   * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
   * requires it in order to read binary files.
   */

  /* Step 1: allocate and initialize JPEG decompression object */

  /* We set up the normal JPEG error routines, then override error_exit. */
  cinfo.err = jpeg_std_error(&jpegError);
  // jerr.pub.error_exit = my_error_exit;
  /* Establish the setjmp return context for my_error_exit to use. */
  // if (setjmp(jerr.setjmp_buffer)) {
  //   /* If we get here, the JPEG code has signaled an error.
  //    * We need to clean up the JPEG object, close the input file, and return.
  //    */
  //   jpeg_destroy_decompress(&cinfo);
  //   fclose(infile);
  //   return 0;
  // }
  /* Now we can initialize the JPEG decompression object. */
  jpeg_create_decompress(&cinfo);

  /* Step 2: specify data source (eg, a file) */

  jpeg_mem_src(&cinfo, reinterpret_cast<const unsigned char*>(imageSource.c_str()), imageSource.size());

  /* Step 3: read file parameters with jpeg_read_header() */

  (void) jpeg_read_header(&cinfo, TRUE);
  /* We can ignore the return value from jpeg_read_header since
   *   (a) suspension is not possible with the stdio data source, and
   *   (b) we passed TRUE to reject a tables-only JPEG file as an error.
   * See libjpeg.doc for more info.
   */

  /* Step 4: set parameters for decompression */

  /* In this example, we don't need to change any of the defaults set by
   * jpeg_read_header(), so we do nothing here.
   */

  /* Step 5: Start decompressor */

  (void) jpeg_start_decompress(&cinfo);
  /* We can ignore the return value since suspension is not possible
   * with the stdio data source.
   */

  /* We may need to do some setup of our own at this point before reading
   * the data.  After jpeg_start_decompress() we have the correct scaled
   * output image dimensions available, as well as the output colormap
   * if we asked for color quantization.
   * In this example, we need to make an output work buffer of the right size.
   */
  /* JSAMPLEs per row in output buffer */
  row_stride = cinfo.output_width * cinfo.output_components;
  /* Make a one-row-high sample array that will go away when done with image */
  buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

  /* Step 6: while (scan lines remain to be read) */
  /*           jpeg_read_scanlines(...); */

  /* Here we use the library's state variable cinfo.output_scanline as the
   * loop counter, so that we don't have to keep track ourselves.
   */

   ColorImage * finalImage = new ColorImage(cinfo.output_width, cinfo.output_height);
   
  while (cinfo.output_scanline < cinfo.output_height) {
    /* jpeg_read_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could ask for
     * more than one scanline at a time if that's more convenient.
     */
    (void) jpeg_read_scanlines(&cinfo, buffer, 1);
    /* Assume put_scanline_someplace wants a pointer and sample count. */
    // put_scanline_someplace(buffer[0], row_stride);

    for (size_t x = 0; x < finalImage->width(); x++) {
      ColorPixel &p = finalImage->pixel(x, cinfo.output_scanline - 1);
      p.red = buffer[0][x*3];
      p.green = buffer[0][x*3+1];
      p.blue = buffer[0][x*3+2];
    }
  }

  /* Step 7: Finish decompression */

  (void) jpeg_finish_decompress(&cinfo);
  /* We can ignore the return value since suspension is not possible
   * with the stdio data source.
   */

  /* Step 8: Release JPEG decompression object */

  /* This is an important step since it will release a good deal of memory. */
  jpeg_destroy_decompress(&cinfo);

  /* After finish_decompress, we can close the input file.
   * Here we postpone it until after no more JPEG errors are possible,
   * so as to simplify the setjmp error logic above.  (Actually, I don't
   * think that jpeg_destroy can do an error exit, but why assume anything...)
   */

  /* At this point you may want to check to see whether any corrupt-data
   * warnings occurred (test whether jerr.pub.num_warnings is nonzero).
   */



  /* And we're done! */
  return finalImage;
}

std::ostream &operator<<(std::ostream &os, const ColorPixel &pixel)
{
  return os << pixel.red << ' ' << pixel.green << ' ' << pixel.blue;
}

std::istream &operator>>(std::istream &is, ColorPixel &pixel)
{
  return is >> pixel.red >> pixel.green >> pixel.blue;
}
