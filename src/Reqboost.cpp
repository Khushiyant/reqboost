#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // For automatic conversion of STL types

// Include the C++ libcurl functions
#include "bindings/ApiBindings.cpp"

namespace py = pybind11;

PYBIND11_MODULE(reqboost, m) {
     m.doc() = "Python package for HTTP requests based on C++ libcurl";

     bind_api(m);
}
