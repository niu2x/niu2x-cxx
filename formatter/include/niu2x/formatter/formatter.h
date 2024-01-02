#ifndef NIU2X_FORMATTER_FORMATTER_H
#define NIU2X_FORMATTER_FORMATTER_H

#include <niu2x/base_stream.h>

namespace niu2x {

class Formatter {
public:
    virtual ~Formatter() { }
    virtual void format(ByteWriteStream* output, int i) = 0;
};

} // namespace niu2x

#endif
