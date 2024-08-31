#ifndef SESSION_H
#define SESSION_H

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>
#include <curl/curl.h>

#include "Models.h"

namespace py = pybind11;

namespace Reqboost
{
    namespace Sessions
    {
        class Session
        {
        private:
            CURL *curl;

        public:
            Session();
            ~Session() = default;

            Models::Response request(const std::string &method, const std::string &url, const py::kwargs kwargs);
            Models::Response get(const std::string &url, const py::dict params = py::none(), py::kwargs kwargs = {});
            Models::Response post(const std::string &url, const py::dict data = py::none(), py::kwargs kwargs = {});
            Models::Response put(const std::string &url, const py::dict data = py::none(), py::kwargs kwargs = {});
            Models::Response patch(const std::string &url, const py::dict data = py::none(), py::kwargs kwargs = {});
            Models::Response remove(const std::string &url, py::kwargs kwargs = {});
            Models::Response head(const std::string &url, py::kwargs kwargs = {});
            Models::Response options(const std::string &url, py::kwargs kwargs = {});

            Session* __enter__();

            void __exit__(const py::object &exc_type, const py::object &exc_value, const py::object &traceback);
        };

        // Callback function to write data received from libcurl
        size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output);

    } // namespace Sessions

} // namespace Reqboost

#endif // SESSION_H