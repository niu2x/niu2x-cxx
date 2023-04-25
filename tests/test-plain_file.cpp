#include <cstdio>
#include <utility>
#include <gtest/gtest.h>
#include <nxc/nxc.h>

using namespace nxc;

TEST(PlainFile, open_read_non_exist)
{
    auto stream_factory = StreamFactory::get();
    auto file = stream_factory->create_read_stream("./non-exist.txt");
    EXPECT_EQ(file.error(), E::OS_ERROR);
}

TEST(PlainFile, open_read_exist)
{
    auto stream_factory = StreamFactory::get();
    auto file = stream_factory->create_read_stream("./test-plain_file");
    EXPECT_EQ(file.error(), E::OK);
}

TEST(PlainFile, write)
{
    auto stream_factory = StreamFactory::get();
    auto file = stream_factory->create_write_stream("./test.txt");
    EXPECT_EQ(file.error(), E::OK);

    auto write_result = (*file)->writex("hello world", 11);
    EXPECT_EQ(write_result.error(), E::OK);
}

TEST(PlainFile, read)
{
    auto stream_factory = StreamFactory::get();
    auto file = stream_factory->create_read_stream("./test.txt");
    EXPECT_EQ(file.error(), E::OK);

    char buffer[32] = { 0 };
    auto read_result = (*file)->read(buffer, 32);
    EXPECT_EQ(read_result.error(), E::OK);
    EXPECT_EQ(*read_result, 11);
    EXPECT_STREQ(buffer, "hello world");
    read_result = (*file)->read(buffer, 1);
    EXPECT_EQ(read_result.error(), E::END_OF_FILE);
}
