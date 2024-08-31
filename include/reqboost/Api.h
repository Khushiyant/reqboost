#ifndef API_H
#define API_H

#include <string>
#include <curl/curl.h>
#include <pybind11/pybind11.h>
#include "Models.h"
#include "Sessions.h"

namespace py = pybind11;
namespace Reqboost
{
    namespace Api
    {
        Models::Response request(const std::string &method, const std::string &url, const py::kwargs kwargs);
        
        Models::Response get(const std::string &url, const py::dict params = py::none(), py::kwargs kwargs = {});
        Models::Response post(const std::string &url, const py::dict data = py::none(), py::kwargs kwargs = {});
        Models::Response put(const std::string &url, const py::dict data = py::none(), py::kwargs kwargs = {});
        Models::Response patch(const std::string &url, const py::dict data = py::none(), py::kwargs kwargs = {});
        Models::Response remove(const std::string &url, py::kwargs kwargs = {});
        Models::Response head(const std::string &url, py::kwargs kwargs = {});
        Models::Response options(const std::string &url, py::kwargs kwargs = {});
    }
}

#endif // API_H
