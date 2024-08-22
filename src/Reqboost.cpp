#include <pybind11/pybind11.h>
#include "Utility.h"

namespace py = pybind11;

PYBIND11_MODULE(reqboost, m)
{
    m.doc() = "Reqboost: A C++ implementation of the requests library";

    // Bindings for the Utility functions
    m.def("url_encode", &Utility::urlEncode);
}