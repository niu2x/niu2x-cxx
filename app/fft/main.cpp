#include <niu2x/math.h>
using namespace niu2x;
int main()
{
    Vector<double> samples;

    double n;
    while (std::cin >> n) {
        samples.push_back(n);
    }

    auto fft_result
        = math::fft(samples.data(), samples.data() + samples.size());
    for (auto& x : fft_result) {
        std::cout << x << std::endl;
    }
    std::cout << std::endl;
    return 0;
}