#include <niu2x/image/image_data.h>
#include <niu2x/stream/buffer_stream.h>
#include <niu2x/disable_windows_warning.h>

#define STBI_NO_STDIO
#include "stb_image.h"

#define STBI_WRITE_NO_STDIO
#include "stb_image_write.h"

namespace niu2x::image {

static auto image_decode(
    const Buffer* buffer, IntSize* size, int* channels_in_file)
{
    return stbi_load_from_memory(buffer->data(),
        static_cast<int>(buffer->size()), &size->width, &size->height,
        channels_in_file, 0);
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

ImageData::ImageData()
: size_ { .width = 0, .height = 0 }
, store_format_(Format::PNG)
, channels_(0)
{
}

ImageData::~ImageData() { }

void ImageData::reset(int w, int h, int channels)
{
    size_ = { .width = w, .height = h };
    channels_ = channels;
    pixels_.resize(size_.area() * channels_);
}

void ImageData::store_to(WriteStream* dest)
{
    switch (store_format_) {
        case Format::PNG: {
            image_png_encode(dest, size_, channels_, pixels_.data());
            break;
        }
        case Format::JPG: {
            image_jpg_encode(dest, size_, channels_, pixels_.data());
            break;
        }
    }
}

void ImageData::load_from(ReadStream* src)
{
    stream::BufferWriteStream file_content_writer;

    pipe(src, &file_content_writer);

    auto& file_content = file_content_writer.buffer();

    auto image_data = image_decode(&file_content, &size_, &channels_);

    if (!image_data) {
        throw_runtime_err(stbi_failure_reason());
    }

    pixels_.resize(size_.area() * channels_);
    memcpy(pixels_.data(), image_data, pixels_.size());

    stbi_image_free(image_data);
}

} // namespace niu2x::image
