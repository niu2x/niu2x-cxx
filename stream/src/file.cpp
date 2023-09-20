#include <niu2x/stream/file.h>

namespace niu2x::stream {

File::File(const fs::File& file, OpenMode open_mode)
: fp_(nullptr)
, path_(file.path())
{
    assert(open_mode == OpenMode::READ || open_mode == OpenMode::WRITE);
    fp_ = fopen(file.c_path(), open_mode == OpenMode::READ ? "rb" : "wb");

    if (!fp_)
        throw_runtime_err("fopen fail: " + file.path().string());
}

File::~File() { fclose(fp_); }

} // namespace niu2x::stream