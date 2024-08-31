#include "bindings/ApiBindings.h"

namespace py = pybind11;

void bind_api(py::module_ &m)
{
      m.def("get",
            &Reqboost::Api::get,
            "Perform an HTTP GET request and return the response",
            py::arg("url"),
            py::arg("params") = py::dict(),
            py::kw_only());

      m.def("post",
            &Reqboost::Api::post,
            "Perform an HTTP POST request and return the response",
            py::arg("url"),
            py::arg("data") = py::dict(),
            py::kw_only());

      m.def("put",
            &Reqboost::Api::put,
            "Perform an HTTP PUT request and return the response",
            py::arg("url"),
            py::arg("data") = py::dict(),
            py::kw_only());

      m.def("remove",
            &Reqboost::Api::remove,
            "Perform an HTTP DELETE request and return the response",
            py::arg("url"),
            py::kw_only());

      m.def("head",
            &Reqboost::Api::head,
            "Perform an HTTP HEAD request and return the response",
            py::arg("url"),
            py::kw_only());

      m.def("patch",
            &Reqboost::Api::patch,
            "Perform an HTTP PATCH request and return the response",
            py::arg("url"),
            py::arg("data") = py::dict(),
            py::kw_only());

      m.def("options",
            &Reqboost::Api::options,
            "Perform an HTTP OPTIONS request and return the response",
            py::arg("url"),
            py::kw_only());
}
