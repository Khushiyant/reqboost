#include <pybind11/pybind11.h>
#include "Api.h"

namespace py = pybind11;

void bind_api(py::module_ &m)
{
    m.def("get", &Reqboost::Api::get, "Perform an HTTP GET request and return the response");
}
