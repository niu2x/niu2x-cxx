#include <nxc/stream.h>


namespace nxc {

class Stdout : public WriteStream {
public:
    Stdout() { }
    virtual ~Stdout() { }

protected:
    virtual Result<size_t> _write(const void* buf, size_t n) override
    {
        if (fwrite(buf, 1, n, stdout) < n)
            return E::OS_ERROR;
        return n;
    }
};

static Stdout stdout_instance;

WriteStream* const out = &stdout_instance;

} // namespace nxc