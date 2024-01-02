#ifndef NIU2X_STREAM_PUSHBACK_READ_STREAM_H
#define NIU2X_STREAM_PUSHBACK_READ_STREAM_H

#include <niu2x/type.h>

namespace niu2x::stream {

class PushBackReadStream : public ReadStream {
public:
    PushBackReadStream(ReadStream*);
    virtual ~PushBackReadStream();
    virtual size_t read(void* buf, size_t size) override;
    virtual bool eof() override;

    void push_back(const void* buf, size_t size);

private:
    Vector<uint8_t> push_back_buffer_;
    ReadStream* delegate_;
};

} // namespace niu2x::stream

#endif
