#include <niu2x/stream.h>

namespace niu2x {

ReadStream::~ReadStream() { }
WriteStream::~WriteStream() { }

void pipe(ReadStream* reader, WriteStream* writer, bool auto_finalize)
{
    constexpr int bs = 4096;
    uint8_t block[bs];
    while (!reader->eof()) {
        auto n = reader->read(block, bs);
        writer->write(block, n);
    }
    if (auto_finalize) {
        writer->finalize();
    }
}

} // namespace niu2x