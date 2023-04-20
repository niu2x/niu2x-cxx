#include <nxc/nxc.h>

void f(int a, char b) {
  nxc::unused(a);
  nxc::unused(a, b);
}

int main() { return 0; }