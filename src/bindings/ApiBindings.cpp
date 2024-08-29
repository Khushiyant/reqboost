#include <pybind11/pybind11.h>
#include "Api.h"
#include "Models.h"
#include "bindings/ApiBindings.h"

namespace py = pybind11;

void bind_api(py::module_ &m)
{
    m.def("get",
          &Reqboost::Api::get,
          "Perform an HTTP GET request and return the response",
          py::arg("url"),
          py::arg("params") = std::map<std::string, std::string>(),
          py::arg("kwargs") = Reqboost::Models::RequestOptions());

    m.def("post",
          &Reqboost::Api::post,
          "Perform an HTTP POST request and return the response",
          py::arg("url"),
          py::arg("data") = std::map<std::string, std::string>(),
          py::arg("kwargs") = Reqboost::Models::RequestOptions());

    m.def("put",
          &Reqboost::Api::put,
          "Perform an HTTP PUT request and return the response",
          py::arg("url"),
          py::arg("data") = std::map<std::string, std::string>(),
          py::arg("kwargs") = Reqboost::Models::RequestOptions());

    m.def("remove",
          &Reqboost::Api::remove,
          "Perform an HTTP DELETE request and return the response",
          py::arg("url"),
          py::arg("kwargs") = Reqboost::Models::RequestOptions());

    m.def("head",
          &Reqboost::Api::head,
          "Perform an HTTP HEAD request and return the response",
          py::arg("url"),
          py::arg("kwargs") = Reqboost::Models::RequestOptions());

    m.def("patch",
          &Reqboost::Api::patch,
          "Perform an HTTP PATCH request and return the response",
          py::arg("url"),
          py::arg("data") = std::map<std::string, std::string>(),
          py::arg("kwargs") = Reqboost::Models::RequestOptions());

    m.def("options",
          &Reqboost::Api::options,
          "Perform an HTTP OPTIONS request and return the response",
          py::arg("url"),
          py::arg("kwargs") = Reqboost::Models::RequestOptions());
}
