#include <niu2x/image.h>
#include <niu2x/stream/push_back_read_stream.h>
#include <niu2x/stream/buffer_stream.h>

#define STBI_NO_STDIO
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace niu2x {

static auto image_decode(
    const Buffer* buffer, IntSize* size, int desired_channels)
{
    int channels_in_file;
    return stbi_load_from_memory(buffer->data(), buffer->size(), &size->width,
        &size->height, &channels_in_file, desired_channels);
}

Image::Image()
: size_ { .width = 0, .height = 0 }
// , channel_(0)
{
}

Image::~Image() { }

void Image::store_to(WriteStream* dest) { unused(dest); }

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
    memcpy(pixels_.data(), image_data, pixels_.size());

    stbi_image_free(image_data);
}

} // namespace niu2x
