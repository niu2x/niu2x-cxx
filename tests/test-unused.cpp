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
        uint8_t buf[512];
        do {
            auto ret = in.readx(buf, 32);
            if (ret) {
                buf[32] = 0;
                printf("%s", buf);
            } else if (ret.error() != nxc::E::WAIT_IO)
                break;
        } while (true);
    }

    // nxc::FileWriteStream out("/home/niu2x/project/nxc/test.txt");
    // if (out) {
    //     for (auto i = 0; i < 1025; i++)
    //         out.write('H');
    // }

    return 0;
}