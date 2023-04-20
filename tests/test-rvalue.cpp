#include <cstdio>
#include <utility>

class STU {
};

static void f(STU&) { printf("lvalue reference\n"); }

static void f(STU&&) { printf("rvalue reference\n"); }

int main()
{
    STU stu;
    STU& stu1 = stu;
    STU&& stu2 = STU();
    f(stu);
    f(std::move(stu1));
    f(stu2);
    return 0;
}