#include <cstdio>
#include <utility>
#include <gtest/gtest.h>
#include <nxc/nxc.h>

class STU {
};

enum class ValueCategory {
    ConstLeft,
    Left,
    Right,
};

static ValueCategory f(const STU&) { return ValueCategory::ConstLeft; }
static ValueCategory f(STU&) { return ValueCategory::Left; }
static ValueCategory f(STU&&) { return ValueCategory::Right; }

template <class T>
static ValueCategory f1(T&& t)
{
    return f(std::forward<T>(t));
}

TEST(rvalue, function_call)
{
    STU stu;
    STU& stu1 = stu;
    STU&& stu2 = STU();
    const STU& stu3 = stu;

    EXPECT_EQ(f(stu), ValueCategory::Left);
    EXPECT_EQ(f(stu1), ValueCategory::Left);
    EXPECT_EQ(f(std::move(stu1)), ValueCategory::Right);
    EXPECT_EQ(f(stu2), ValueCategory::Left);
    EXPECT_EQ(f(STU()), ValueCategory::Right);

    EXPECT_EQ(f1(stu), ValueCategory::Left);
    EXPECT_EQ(f1(stu1), ValueCategory::Left);
    EXPECT_EQ(f1(stu2), ValueCategory::Left);
    EXPECT_EQ(f1(stu3), ValueCategory::ConstLeft);
    EXPECT_EQ(f1(STU()), ValueCategory::Right);
    EXPECT_EQ(f1(std::move(stu1)), ValueCategory::Right);
    EXPECT_EQ(f1(std::move(stu2)), ValueCategory::Right);
    EXPECT_EQ(f1(std::move(stu)), ValueCategory::Right);
}
