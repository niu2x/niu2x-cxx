#include <nxc/nxc.h>

void f(int a, char b) {
    nxc::unused(a);
    nxc::unused(a, b);
}

class A {
public:
    char x;
    int a;
};

int main()
{
    A a;
    printf("&a.a = %p\n", &A::a);
    printf("&A.a = %p\n", &a.a);
    nxc::FileReadStream fs;
    if (fs.open("/home/niu2x/project/nxc/CMakeLists.txt")) {
        while (auto ch = fs.read()) {
            putchar(*ch);
        }
    }

    return 0;
}