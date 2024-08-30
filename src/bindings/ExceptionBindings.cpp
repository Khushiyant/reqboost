#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // For automatic conversion of STL types


#include "Exceptions.h"
#include "bindings/ExceptionBindings.h"

namespace py = pybind11;

void bind_exceptions(py::module_ &m)
{
    py::register_exception<Reqboost::Exceptions::RequestException>(m, "RequestException");
    py::register_exception<Reqboost::Exceptions::InvalidJSONError>(m, "InvalidJSONError");
    py::register_exception<Reqboost::Exceptions::JSONDecodeError>(m, "JSONDecodeError");
    py::register_exception<Reqboost::Exceptions::HTTPError>(m, "HTTPError");
    py::register_exception<Reqboost::Exceptions::ConnectionError>(m, "ConnectionError");
    py::register_exception<Reqboost::Exceptions::ProxyError>(m, "ProxyError");
    py::register_exception<Reqboost::Exceptions::SSLError>(m, "SSLError");
    py::register_exception<Reqboost::Exceptions::Timeout>(m, "Timeout");
    py::register_exception<Reqboost::Exceptions::ConnectTimeout>(m, "ConnectTimeout");
    py::register_exception<Reqboost::Exceptions::ReadTimeout>(m, "ReadTimeout");
    py::register_exception<Reqboost::Exceptions::URLRequired>(m, "URLRequired");
    py::register_exception<Reqboost::Exceptions::TooManyRedirects>(m, "TooManyRedirects");
    py::register_exception<Reqboost::Exceptions::MissingSchema>(m, "MissingSchema");
    py::register_exception<Reqboost::Exceptions::InvalidSchema>(m, "InvalidSchema");
    py::register_exception<Reqboost::Exceptions::InvalidURL>(m, "InvalidURL");
    py::register_exception<Reqboost::Exceptions::InvalidHeader>(m, "InvalidHeader");
    py::register_exception<Reqboost::Exceptions::InvalidProxyURL>(m, "InvalidProxyURL");
    py::register_exception<Reqboost::Exceptions::ChunkedEncodingError>(m, "ChunkedEncodingError");
    py::register_exception<Reqboost::Exceptions::ContentDecodingError>(m, "ContentDecodingError");
    py::register_exception<Reqboost::Exceptions::StreamConsumedError>(m, "StreamConsumedError");
    py::register_exception<Reqboost::Exceptions::RetryError>(m, "RetryError");
    py::register_exception<Reqboost::Exceptions::UnrewindableBodyError>(m, "UnrewindableBodyError");
    py::register_exception<Reqboost::Exceptions::RequestsWarning>(m, "RequestsWarning");
    py::register_exception<Reqboost::Exceptions::FileModeWarning>(m, "FileModeWarning");
    py::register_exception<Reqboost::Exceptions::RequestsDependencyWarning>(m, "RequestsDependencyWarning");
}