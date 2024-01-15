#include <pybind11/pybind11.h>

static int add(int i, int j) { return i + j; }

PYBIND11_MODULE(niu2py, m)
{
    m.doc() = "niu2py"; // optional module docstring

    auto media = m.def_submodule("media", "This is media submodule");
    media.def("func", &module_a::func);
}
