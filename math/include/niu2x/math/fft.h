#ifndef NIU2X_MATH_FFT_H
#define NIU2X_MATH_FFT_H

#include <niu2x/std_alias.h>
#include <niu2x/math/complex.h>

namespace niu2x::math {

Vector<Complex> fft(double* begin, double* end);
}

#endif