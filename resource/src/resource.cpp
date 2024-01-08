#include <niu2x/resource/resource.h>
#include <niu2x/stream.h>

namespace niu2x {

Resource::~Resource() { }

void Resource::load_from_file(const fs::AbsPath& path)
{
    fs::File file(path);
    stream::FileByteReadStream input_s(file);
    load_from(&input_s);
}

void Resource::store_to_file(const fs::AbsPath& path)
{
    fs::File file(path);
    stream::FileByteWriteStream output_s(file);
    store_to(&output_s);
}

} // namespace niu2x