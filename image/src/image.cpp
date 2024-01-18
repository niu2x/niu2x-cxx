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
, channels_(0)
// , store_format_(Format::PNG)
{
}

Image::~Image() { }

void Image::reset(int w, int h, int channels)
{
    size_ = { .width = w, .height = h };
    pixels_.resize(size_.area() * channels * bytes_per_channel_);
    channels_ = channels;
}

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

Image::Image(Image&& other) noexcept
: size_(other.size_)
, pixels_(std::move(other.pixels_))
, bytes_per_channel_(other.bytes_per_channel_)
, channels_(other.channels_)
, store_format_(other.store_format_)
{
    other.size_ = { 0, 0 };
    other.channels_ = 0;
}

Image& Image::operator=(Image&& other) noexcept
{
    Image tmp(std::move(other));
    swap(tmp);
    return *this;
}

void Image::swap(Image& other) noexcept
{
    niu2x::swap(size_, other.size_);
    niu2x::swap(pixels_, other.pixels_);
    niu2x::swap(bytes_per_channel_, other.bytes_per_channel_);
    niu2x::swap(channels_, other.channels_);
    niu2x::swap(store_format_, other.store_format_);
}

void Image::load_from(ByteReadStream* src)
{
    BufferPtr file_content = make_shared<Buffer>();
    stream::BufferByteWriteStream file_content_writer(file_content);

    pipe(src, &file_content_writer);

    auto decode_result = image_decode(file_content.get(), &size_, 0);

    if (!decode_result.image_data) {
        throw_runtime_err(stbi_failure_reason());
    }

    channels_ = decode_result.channels;

    auto total_bytes = size_.area() * bytes_per_channel_ * channels_;
    pixels_.resize(total_bytes);
    memcpy(pixels_.data(), decode_result.image_data, total_bytes);

    stbi_image_free(decode_result.image_data);
}

Image Image::crop(const math::IntRect& sub_region) const
{
    math::IntRect region(0, 0, size_.width, size_.height);
    region = region.intersection(sub_region);

    auto& r_o = region.origin;
    auto& r_s = region.size;

    if (region.area() <= 0)
        return Image();

    Image new_img;
    new_img.reset(r_s.width, r_s.height, channels_);

    auto pixel_size = channels_ * bytes_per_channel_;

    Index new_offset = 0;

    Index offset = pixel_size * (r_o.y * size_.width + r_o.x);

    for (int y = 0; y < r_s.height; y++) {

        for (int x = 0; x < r_s.width; x++) {
            auto* new_ptr = &new_img.pixels_[new_offset];
            auto* ptr = &pixels_[offset];

            memcpy(new_ptr, ptr, pixel_size);

            new_offset += pixel_size;
            offset += pixel_size;
        }

        offset += (size_.width - r_s.width) * pixel_size;
    }

    return new_img;
}

} // namespace niu2x::image
