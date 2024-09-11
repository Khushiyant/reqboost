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

        .def_property_readonly("is_redirect", &Reqboost::Models::Response::is_redirect)
        .def_property_readonly("is_permanent_redirect", &Reqboost::Models::Response::is_permanent_redirect)

        // Dunder methods
        .def("__repr__", &Reqboost::Models::Response::__repr__)
        .def("__nonzero__", &Reqboost::Models::Response::__nonzero__)
        .def("__bool__", &Reqboost::Models::Response::__bool__)
        // .def("__enter__", &Reqboost::Models::Response::__enter__)

        // Property methods
        .def_property_readonly("text", &Reqboost::Models::Response::text)
        .def_property_readonly("links", &Reqboost::Models::Response::links)
        .def_property_readonly("apparent_encoding", &Reqboost::Models::Response::apparent_encoding)

        // property methods
        .def("ok", &Reqboost::Models::Response::ok);

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

    py::class_<Reqboost::Models::Request>(m, "Request")
        .def(py::init<const std::string&, const std::string&, 
                      const std::map<std::string, std::string>&, 
                      const std::vector<std::pair<std::string, std::string>>&, 
                      const std::vector<std::pair<std::string, std::string>>&, 
                      const std::map<std::string, std::string>&, 
                      const std::map<std::string, std::function<void()>>&>(),
             py::arg("method") = "", py::arg("url") = "", py::arg("headers") = std::map<std::string, std::string>(),
             py::arg("files") = std::vector<std::pair<std::string, std::string>>(),
             py::arg("data") = std::vector<std::pair<std::string, std::string>>(),
             py::arg("params") = std::map<std::string, std::string>(),
             py::arg("hooks") = std::map<std::string, std::function<void()>>()
        )
        .def("prepare", &Reqboost::Models::Request::prepare)
        .def("__repr__", &Reqboost::Models::Request::repr);
        // .def_readwrite("auth", &Reqboost::Models::Request::auth)
        // .def_readwrite("cookies", &Reqboost::Models::Request::cookies)

    py::class_<Reqboost::Models::PreparedRequest, std::shared_ptr<Reqboost::Models::PreparedRequest>>(m, "PreparedRequest")
        .def(py::init<>()) // Default constructor
        .def("prepare", &Reqboost::Models::PreparedRequest::prepare)
        .def("__repr__", &Reqboost::Models::PreparedRequest::repr);
        // .def_readwrite("method", &Reqboost::Models::PreparedRequest::method)
        // .def_readwrite("url", &Reqboost::Models::PreparedRequest::url)
        // .def_readwrite("headers", &Reqboost::Models::PreparedRequest::headers)
        // .def_readwrite("body", &Reqboost::Models::PreparedRequest::body)
        // .def("copy", &Reqboost::Models::PreparedRequest::copy);
}
