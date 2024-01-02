#include <niu2x/stream/file.h>

using si = std::ios_base;

namespace niu2x::stream {

File::File(const fs::File& file, OpenMode open_mode)
: fp_(nullptr)
, path_(file.path())
{
    // assert(open_mode == OpenMode::READ || open_mode == OpenMode::WRITE);
    si::openmode mode = open_mode == OpenMode::READ ? si::in : si::out;

    fp_.open(file.path().native(), mode);

    if (!fp_.is_open())
        throw_runtime_err("fopen fail: " + file.path().str());

    fp_.exceptions(std::ifstream::failbit);
    fp_.exceptions(std::ifstream::badbit);
}

File::~File() { fp_.close(); }

} // namespace niu2x::stream