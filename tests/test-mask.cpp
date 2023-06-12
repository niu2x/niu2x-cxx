#include <cstdio>
#include <utility>
#include <gtest/gtest.h>

#include <nxc/nxc.h>

using namespace nxc;

TEST(Mask, constructor)
{
    Mask<uint8_t> a;
    EXPECT_EQ(0, a.value());

    Mask<uint16_t> b;
    EXPECT_EQ(0, b.value());

    Mask<int> c;
    EXPECT_EQ(0, c.value());
}

TEST(Mask, from_bit)
{
    auto a = Mask<uint8_t>::from_bit(0);
    EXPECT_EQ(1, a.value());

    auto b = Mask<uint8_t>::from_bit(1);
    EXPECT_EQ(2, b.value());

    auto c = Mask<uint8_t>::from_bit(1, 2);
    EXPECT_EQ(6, c.value());
}

TEST(Mask, assgin)
{
    auto a = Mask<uint8_t>::from_bit(0);
    auto b = Mask<uint8_t>::from_bit(1);
    a = b;
    EXPECT_EQ(2, a.value());

    a = Mask<uint8_t>::Zero;
    EXPECT_EQ(0, a.value());
    EXPECT_EQ(Mask<uint8_t>::Zero, a);
}

TEST(Mask, calc)
{
    auto a = Mask<int>::from_bit(3);
    auto b = Mask<int>::from_bit(1);

    EXPECT_EQ(10, (a | b).value());
    EXPECT_EQ(0, (a & b).value());

    b.set_bit(0);
    EXPECT_EQ(3, b.value());

    b.reset_bit(0);
    EXPECT_EQ(2, b.value());
    b.reset_bit(1);
    EXPECT_EQ(0, b.value());
}