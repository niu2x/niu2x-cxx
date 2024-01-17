#include <niu2x/math/fft.h>
#include <niu2x/convention.h>
#include <niu2x/exception.h>
#include <niu2x/unused.h>
#include "build_time/build_config.h"

#if NIU2X_USE_FFT
    #include <fftw3.h>
#endif

namespace niu2x::math {

Vector<Complex> fft(double* begin, double* end)
{
    Vector<Complex> result;

#if NIU2X_USE_FFT
    NR N = end - begin;

    auto* data = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
    // 初始化数据
    for (Index i = 0; i < N; i++) {
        data[i][0] = begin[i];
        data[i][1] = 0; // 虚数部分
    }

    auto* fft_result = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);

    auto plan = fftw_plan_dft_1d(N, data, fft_result, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);

    for (Index i = 0; i < N; i++) {
        result.emplace_back(fft_result[i][0], fft_result[i][1]);
    }

    fftw_destroy_plan(plan);
    fftw_free(data);
    fftw_free(fft_result);

#else
    unused(begin);
    unused(end);
    throw_runtime_err("this build is not support fft");
#endif

    return result;
}

} // namespace niu2x::math