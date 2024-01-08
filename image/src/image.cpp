#include <niu2x/image/image.h>
#include <niu2x/stream/buffer_stream.h>
#include <niu2x/exception.h>

#include <niu2x/disable_windows_warning.h>

#define STBI_NO_STDIO
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_WRITE_NO_STDIO
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace niu2x::image {

struct ImageDecodeResult {
    uint8_t* image_data;
    int channels;
};
static ImageDecodeResult
image_decode(const Buffer* buffer, IntSize* size, int desired_channels)
{
    int channels_in_file;
    return { stbi_load_from_memory(
                 buffer->data(),
                 static_cast<int>(buffer->size()),
                 &size->width,
                 &size->height,
                 &channels_in_file,
                 desired_channels),
             channels_in_file };
}

static void stbi_write_callback(void* context, void* data, int size)
{
    ByteWriteStream* writer = reinterpret_cast<ByteWriteStream*>(context);
    writer->write(reinterpret_cast<uint8_t*>(data), size);
}

static int image_png_encode(
    ByteWriteStream* writer,
    IntSize size,
    int comp,
    const void* data)
{
    return stbi_write_png_to_func(
        stbi_write_callback,
        writer,
        size.width,
        size.height,
        comp,
        data,
        0);
}

static int image_jpg_encode(
    ByteWriteStream* writer,
    IntSize size,
    int comp,
    const void* data)
{
    return stbi_write_jpg_to_func(
        stbi_write_callback,
        writer,
        size.width,
        size.height,
        comp,
        data,
        100);
}

Image::Image()
: size_ { .width = 0, .height = 0 }
// , store_format_(Format::PNG)
// , channel_(0)
{
}

Image::~Image() { }

// void Image::reset(int w, int h, const Color& color)
// {
//     size_ = { .width = w, .height = h };
//     pixels_.resize(size_.area());
//     for (int row = 0; row < h; row++)
//         for (int col = 0; col < w; col++) {
//             set_pixel(row, col, color);
//         }
// }

void Image::store_to(ByteWriteStream* dest) const
{
    switch (store_format_) {
        case FileFormat::PNG: {
            image_png_encode(dest, size_, channels_, pixels_.data());
            break;
        }
        case FileFormat::JPG: {
            image_jpg_encode(dest, size_, channels_, pixels_.data());
            break;
        }
    }
}

void Image::load_from(ByteReadStream* src)
{
    stream::BufferByteWriteStream file_content_writer;

    pipe(src, &file_content_writer);

    auto file_content = file_content_writer.buffer();

    auto decode_result = image_decode(file_content, &size_, 0);

    if (!decode_result.image_data) {
        throw_runtime_err(stbi_failure_reason());
    }

    channels_ = decode_result.channels;

    auto total_bytes = size_.area() * bytes_per_channel * channels_;
    pixels_.resize(total_bytes);
    memcpy(pixels_.data(), decode_result.image_data, total_bytes);

    stbi_image_free(decode_result.image_data);
}

} // namespace niu2x::image
