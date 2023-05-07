#include <cstdio>
#include <utility>
#include <gtest/gtest.h>

#include <nxc/nxc.h>

using namespace nxc;

TEST(Ptr, equal)
{
    auto ptr = NXC_MAKE_PTR(int, 1);
    Ptr<int> ptr1 = ptr;
    Ptr<int> ptr2;

    EXPECT_EQ(ptr, ptr1);
    EXPECT_EQ(ptr2, nullptr);

    ptr1 = nullptr;
    EXPECT_EQ(ptr1, nullptr);
}

TEST(Ptr, not_equal)
{
    auto ptr = NXC_MAKE_PTR(int, 1);
    Ptr<int> ptr1 = NXC_MAKE_PTR(int, 1);
    EXPECT_NE(ptr, ptr1);
}
