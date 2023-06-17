#include <cstdio>
#include <utility>
#include <gtest/gtest.h>

#include <nxc/nxc.h>

using namespace nxc;

TEST(Bitmask, constructor)
{
    Bitmask<uint8_t> a;
    EXPECT_EQ(0, a.get());

    Bitmask<uint16_t> b;
    EXPECT_EQ(0, b.get());

    Bitmask<int> c;
    EXPECT_EQ(0, c.get());
}

TEST(Bitmask, from_bit)
{
    auto a = Bitmask<uint8_t>::from_bit(0);
    EXPECT_EQ(1, a.get());

    auto b = Bitmask<uint8_t>::from_bit(1);
    EXPECT_EQ(2, b.get());

    auto c = Bitmask<uint8_t>::from_bit(1, 2);
    EXPECT_EQ(6, c.get());
}

TEST(Bitmask, assgin)
{
    auto a = Bitmask<uint8_t>::from_bit(0);
    auto b = Bitmask<uint8_t>::from_bit(1);
    a = b;
    EXPECT_EQ(2, a.get());

    a = Bitmask<uint8_t>::Zero;
    EXPECT_EQ(0, a.get());
    EXPECT_EQ(Bitmask<uint8_t>::Zero, a);
}

TEST(Bitmask, calc)
{
    auto a = Bitmask<int>::from_bit(3);
    auto b = Bitmask<int>::from_bit(1);

    EXPECT_EQ(10, (a | b).get());
    EXPECT_EQ(0, (a & b).get());

    b.set_bit(0);
    EXPECT_EQ(3, b.get());

    b.reset_bit(0);
    EXPECT_EQ(2, b.get());
    b.reset_bit(1);
    EXPECT_EQ(0, b.get());
}