#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Models.h" // Include the header where Response, ParsedURL, and RequestOptions are defined
#include "bindings/ModelsBindings.h"

namespace py = pybind11;

void bind_models(py::module_ &m)
{
    py::class_<Reqboost::Models::Response>(m, "Response")
        .def(py::init<>()) // Bind the default constructor
        .def_readwrite("_content", &Reqboost::Models::Response::_content)
        .def_readwrite("status_code", &Reqboost::Models::Response::status_code)
        .def_readwrite("headers", &Reqboost::Models::Response::headers)
        .def_readwrite("url", &Reqboost::Models::Response::url)
        .def_readwrite("history", &Reqboost::Models::Response::history)
        .def_readwrite("encoding", &Reqboost::Models::Response::encoding)
        .def_readwrite("reason", &Reqboost::Models::Response::reason)
        .def_readwrite("cookies", &Reqboost::Models::Response::cookies)
        .def_readwrite("elapsed", &Reqboost::Models::Response::elapsed)
        .def_readwrite("request", &Reqboost::Models::Response::request)
        .def("__repr__",
             [](const Reqboost::Models::Response &r)
             {
                 return "<Response [" + std::to_string(r.status_code) + "]>";
             });

    py::class_<Reqboost::Models::ParsedURL>(m, "ParsedURL")
        .def(py::init<>())
        .def_readwrite("scheme", &Reqboost::Models::ParsedURL::scheme)
        .def_readwrite("host", &Reqboost::Models::ParsedURL::host)
        .def_readwrite("path", &Reqboost::Models::ParsedURL::path)
        .def_readwrite("query", &Reqboost::Models::ParsedURL::query)
        .def_readwrite("fragment", &Reqboost::Models::ParsedURL::fragment);

    py::class_<Reqboost::Models::RequestOptions>(m, "RequestOptions")
        .def(py::init<>()) // Bind the default constructor
        .def_readwrite("params", &Reqboost::Models::RequestOptions::params)
        .def_readwrite("data", &Reqboost::Models::RequestOptions::data);
}
