#include <niu2x/image.h>
#include <niu2x/stream/push_back_read_stream.h>
#include <niu2x/stream/buffer_stream.h>

#include <niu2x/disable_windows_warning.h>

#define STBI_NO_STDIO
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_WRITE_NO_STDIO
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace niu2x::image {

static auto image_decode(
    const Buffer* buffer, IntSize* size, int desired_channels)
{
    int channels_in_file;
    return stbi_load_from_memory(buffer->data(),
        static_cast<int>(buffer->size()), &size->width, &size->height,
        &channels_in_file, desired_channels);
}

static void stbi_write_callback(void* context, void* data, int size)
{
    WriteStream* writer = reinterpret_cast<WriteStream*>(context);
    writer->write(data, size);
}

static int image_png_encode(
    WriteStream* writer, IntSize size, int comp, const void* data)
{
    return stbi_write_png_to_func(
        stbi_write_callback, writer, size.width, size.height, comp, data, 0);
}

static int image_jpg_encode(
    WriteStream* writer, IntSize size, int comp, const void* data)
{
    return stbi_write_jpg_to_func(
        stbi_write_callback, writer, size.width, size.height, comp, data, 100);
}

Image::Image()
: size_ { .width = 0, .height = 0 }
, store_format_(Format::PNG)
// , channel_(0)
{
}

Image::~Image() { }

void Image::reset(int w, int h, const Color& color)
{
    size_ = { .width = w, .height = h };
    pixels_.resize(size_.area());
    for (int row = 0; row < h; row++)
        for (int col = 0; col < w; col++) {
            set_pixel(row, col, color);
        }
}

void Image::store_to(WriteStream* dest)
{
    int channels = 4;
    switch (store_format_) {
        case Format::PNG: {
            image_png_encode(dest, size_, channels, pixels_.data());
            break;
        }
        case Format::JPG: {
            image_jpg_encode(dest, size_, channels, pixels_.data());
            break;
        }
    }
}

void Image::load_from(ReadStream* src)
{
    Buffer file_content;
    stream::BufferWriteStream file_content_writer(file_content);

    pipe(src, &file_content_writer);

    int desired_channels = 4;

    auto image_data = image_decode(&file_content, &size_, desired_channels);

    if (!image_data) {
        throw_runtime_err(stbi_failure_reason());
    }

    pixels_.resize(size_.area());
    memcpy(pixels_.data(), image_data, pixels_.size() * sizeof(Color));

    stbi_image_free(image_data);
}

} // namespace niu2x::image
