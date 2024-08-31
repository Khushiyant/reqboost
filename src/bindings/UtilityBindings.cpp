#include "bindings/UtilityBindings.h"

namespace py = pybind11;

void bind_utility(py::module_ &m)
{

    m.def("urlencode", &Reqboost::Utility::urlencode, "Encode a string for use in a URL");
    m.def("urldecode", &Reqboost::Utility::urldecode, "Decode a string from a URL");
    m.def("urlunparse", &Reqboost::Utility::urlunparse, "Combine components of a URL into a string");

    m.def("urlsplit", &Reqboost::Utility::urlsplit, "Split a URL into components");

}
