#include <niu2x/math.h>
using namespace niu2x;
int main()
{
    double examples[100];
    for (int i = 0; i < 100; i++)
        examples[i] = sin(i / 10.0 * 2 * 3.1415926 + 3.1415926 * 0.5);

    auto fft_result = math::fft(examples, examples + 100);
    for (auto& x : fft_result) {
        std::cout << x << ",";
    }
    std::cout << std::endl;
    return 0;
}