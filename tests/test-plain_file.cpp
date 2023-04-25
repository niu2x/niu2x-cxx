#include <cstdio>
#include <utility>
#include <gtest/gtest.h>
#include <nxc/nxc.h>

using namespace nxc;

TEST(PlainFile, open_read_non_exist)
{
    auto file_factory = NXC_MAKE_PTR(DefaultFileFactory);
    auto file = file_factory->create("./non-exist.txt");
    EXPECT_EQ(file->open(OpenMode::READ).error(), E::OS_ERROR);
}

TEST(PlainFile, open_read_exist)
{
    auto file_factory = NXC_MAKE_PTR(DefaultFileFactory);
    auto file = file_factory->create("./test-plain_file");
    EXPECT_EQ(file->open(OpenMode::READ).error(), E::OK);
    file->close();
}

TEST(PlainFile, write)
{
    auto file_factory = NXC_MAKE_PTR(DefaultFileFactory);
    auto file = file_factory->create("./test.txt");
    EXPECT_EQ(file->open(OpenMode::WRITE).error(), E::OK);

    auto write_result = file->write("hello world", 11);
    EXPECT_EQ(write_result.error(), E::OK);
    EXPECT_EQ(*write_result, 11);

    file->close();
}

TEST(PlainFile, read)
{
    auto file_factory = NXC_MAKE_PTR(DefaultFileFactory);
    auto file = file_factory->create("./test.txt");
    EXPECT_EQ(file->open(OpenMode::READ).error(), E::OK);

    char buffer[32] = { 0 };
    auto read_result = file->read(buffer, 32);
    EXPECT_EQ(read_result.error(), E::OK);
    EXPECT_EQ(*read_result, 11);
    EXPECT_STREQ(buffer, "hello world");
    read_result = file->read(buffer, 1);
    EXPECT_EQ(read_result.error(), E::END_OF_FILE);
    file->close();
}
