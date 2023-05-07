#include <nxc/stream.h>

namespace nxc {

class Stdin : public ReadStream {
public:
    Stdin() { }
    virtual ~Stdin() { }

protected:
    virtual Result<size_t> _read(void* buf, size_t n) override
    {
        size_t read_n = fread(buf, 1, n, stdin);
        if (read_n == 0) {
            if (feof(stdin)) {
                return E::END_OF_FILE;
            }

            if (ferror(stdin)) {
                return E::OS_ERROR;
            }
        }
        return read_n;
    }
};

const ReadStreamPtr in = NXC_MAKE_PTR(Stdin);

} // namespace nxc