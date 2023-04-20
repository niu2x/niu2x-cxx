#include <cstdio>
#include <utility>
#include <gtest/gtest.h>

class STU {
};

enum class ValueCategory {
    Left,
    Right,
};

static ValueCategory f(STU&) { return ValueCategory::Left; }

static ValueCategory f(STU&&) { return ValueCategory::Right; }

TEST(rvalue, function_call)
{
    STU stu;
    STU& stu1 = stu;
    STU&& stu2 = STU();

    EXPECT_EQ(f(stu), ValueCategory::Left);
    EXPECT_EQ(f(stu1), ValueCategory::Left);
    EXPECT_EQ(f(std::move(stu1)), ValueCategory::Right);
    EXPECT_EQ(f(stu2), ValueCategory::Left);
    EXPECT_EQ(f(STU()), ValueCategory::Right);
}
