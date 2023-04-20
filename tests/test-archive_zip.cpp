#include <nxc/nxc.h>

using namespace nxc;

int main()
{
    auto stream_factory = NXC_MAKE_PTR(DefaultStreamFactory);
    auto archive_factory = NXC_MAKE_PTR(DefaultArchiveFactory);
    auto archive = archive_factory->create("./test.zip");
    {
        NXC_ASSERT(archive->open(O_RW), "");
        auto entry = archive->open_entry("./ABC");
        NXC_ASSERT(entry != nullptr, "");
        NXC_ASSERT(entry->open(O_WRITE), "");
        NXC_ASSERT(entry->write("hello world\0", 12), "");
        entry->close();
        archive->close_entry(entry);
        archive->close();
    }

    {
        NXC_ASSERT(archive->open(O_READ), "read open fail");
        NXC_ASSERT(archive->exist_entry("./ABC"), "");
        archive->close();
    }

    {
        NXC_ASSERT(archive->open(O_RW), "read open fail");
        NXC_ASSERT(archive->exist_entry("./ABC"), "");
        auto entry = archive->open_entry("./ABC");
        NXC_ASSERT(entry->open(O_READ), "");

        {
            auto s = stream_factory->create_read_stream(entry);
            pipe(s.get(), nxc::stdout);
        }

        entry->close();
        archive->close_entry(entry);
        archive->close();
    }

    {
        NXC_ASSERT(archive->open(O_WRITE), "write open fail");
        NXC_ASSERT(!archive->exist_entry("./ABC"), "");
        archive->close();
    }

    return 0;
}