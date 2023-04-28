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

TEST(Buffer, copy)
{
    const char* message = "Hello world!";
    Buffer buffer;
    buffer.write(message, strlen(message));
    EXPECT_EQ(buffer.size(), strlen(message));

    Buffer other(buffer);
    EXPECT_EQ(buffer.size(), other.size());
    EXPECT_STREQ((const char*)buffer.data(), (const char*)other.data());

    other = buffer;
    EXPECT_EQ(buffer.size(), other.size());
    EXPECT_STREQ((const char*)buffer.data(), (const char*)other.data());
}

TEST(Buffer, move)
{
    const char* message = "Hello world!";
    Buffer buffer;
    buffer.write(message, strlen(message));
    EXPECT_EQ(buffer.size(), strlen(message));

    Buffer other(std::move(buffer));
    EXPECT_EQ(other.size(), strlen(message));
    EXPECT_EQ(buffer.size(), 0);

    other = std::move(other);
    EXPECT_EQ(other.size(), strlen(message));

    Buffer other2;
    other2 = std::move(other);
    EXPECT_EQ(other.size(), 0);
    EXPECT_EQ(other2.size(), strlen(message));
}
