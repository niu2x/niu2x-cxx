#include <cstdio>
#include <utility>
#include <gtest/gtest.h>

#include <nxc/nxc.h>

using namespace nxc;

TEST(Buffer, reserve)
{
    Buffer buffer;
    buffer.reserve(1024);

    EXPECT_EQ(buffer.capacity(), 1024);
}

TEST(Buffer, resize)
{
    Buffer buffer;
    buffer.resize(1024, 'A');

    EXPECT_EQ(buffer.size(), 1024);

    for (int i = 0; i < buffer.size(); i++) {
        EXPECT_EQ(buffer.data()[i], 'A');
    }
}

TEST(Buffer, clear)
{
    Buffer buffer;
    buffer.resize(1024, 'A');
    buffer.clear();
    EXPECT_EQ(buffer.size(), 0);
}

TEST(Buffer, write)
{
    const char* message = "Hello world!";
    Buffer buffer;
    buffer.write(message, strlen(message));
    EXPECT_EQ(buffer.size(), strlen(message));

    for (int i = 0; i < buffer.size(); i++) {
        EXPECT_EQ(buffer.data()[i], message[i]);
    }
}
