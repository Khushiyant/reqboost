#include "bindings/SessionBindings.h"

namespace py = pybind11;

void bind_sessions(pybind11::module &m)
{
    // expose the Session class
    py::class_<Reqboost::Sessions::Session>(m, "Session")
        .def(py::init<>())
        .def("__enter__", &Reqboost::Sessions::Session::__enter__) // Enter method for context management
        .def("__exit__", &Reqboost::Sessions::Session::__exit__)   // Exit method for context management
        .def("request", &Reqboost::Sessions::Session::request,
             "Perform an HTTP request and return the response",
             py::arg("method"),
             py::arg("url"),
             py::kw_only())
        .def("get",
             &Reqboost::Sessions::Session::get,
             "Perform an HTTP GET request and return the response",
             py::arg("url"),
             py::arg("params") = py::dict(),
             py::kw_only())
        .def("post",
             &Reqboost::Sessions::Session::post,
             "Perform an HTTP POST request and return the response",
             py::arg("url"),
             py::arg("data") = py::dict(),
             py::kw_only())
        .def("put",
             &Reqboost::Sessions::Session::put,
             "Perform an HTTP PUT request and return the response",
             py::arg("url"),
             py::arg("data") = py::dict(),
             py::kw_only())
        .def("remove",
             &Reqboost::Sessions::Session::remove,
             "Perform an HTTP DELETE request and return the response",
             py::arg("url"),
             py::kw_only())
        .def("head",
             &Reqboost::Sessions::Session::head,
             "Perform an HTTP HEAD request and return the response",
             py::arg("url"),
             py::kw_only())
        .def("patch",
             &Reqboost::Sessions::Session::patch,
             "Perform an HTTP PATCH request and return the response",
             py::arg("url"),
             py::arg("data") = py::dict(),
             py::kw_only())
        .def("options",
             &Reqboost::Sessions::Session::options,
             "Perform an HTTP OPTIONS request and return the response",
             py::arg("url"),
             py::kw_only());
}
