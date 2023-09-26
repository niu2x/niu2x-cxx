#include <niu2x/stream/file.h>

namespace niu2x::stream {

File::File(const fs::File& file, OpenMode open_mode)
: fp_(nullptr)
, path_(file.path())
{
    assert(open_mode == OpenMode::READ || open_mode == OpenMode::WRITE);
    const char* mode = open_mode == OpenMode::READ ? "rb" : "wb";

    fp_ = fopen(reinterpret_cast<const char*>(file.c_path()), mode);

    if (!fp_)
        throw_runtime_err("fopen fail: " + file.path().string());
}

File::~File() { fclose(fp_); }

} // namespace niu2x::stream