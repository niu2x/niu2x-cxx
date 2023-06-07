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
    return 0;
}