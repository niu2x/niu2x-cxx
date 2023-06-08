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
    nxc::FileReadStream in("/home/niu2x/project/nxc/CMakeLists.txt");
    if (in) {
        while (auto ch = in.read()) {
            putchar(*ch);
        }
    }

    nxc::FileWriteStream out("/home/niu2x/project/nxc/CMakeLists.txt");
    if (out) {
        out.write('H');
        //     out.write('e');
        //     out.write('l');
        //     out.write('l');
        //     out.write('o');
    }

    return 0;
}