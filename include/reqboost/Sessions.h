#ifndef SESSION_H
#define SESSION_H

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


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
            ~Session();

            /**
             * @brief Base request method
             *
             * @param method
             * @param url
             * @param kwargs
             * @return Models::Response
             */
            Models::Response request(const std::string &method, const std::string &url, const py::kwargs kwargs);

            /**
             * @brief GET request
             *
             * @param url
             * @param params
             * @param kwargs
             * @return Models::Response
             */
            Models::Response get(const std::string &url, const py::dict params = py::none(), py::kwargs kwargs = {});

            /**
             * @brief POST request
             *
             * @param url
             * @param data
             * @param kwargs
             * @return Models::Response
             */
            Models::Response post(const std::string &url, const py::dict data = py::none(), py::kwargs kwargs = {});

            /**
             * @brief PUT request
             *
             * @param url
             * @param data
             * @param kwargs
             * @return Models::Response
             */
            Models::Response put(const std::string &url, const py::dict data = py::none(), py::kwargs kwargs = {});

            /**
             * @brief PATCH request
             *
             * @param url
             * @param data
             * @param kwargs
             * @return Models::Response
             */
            Models::Response patch(const std::string &url, const py::dict data = py::none(), py::kwargs kwargs = {});

            /**
             * @brief DELETE request
             *
             * @param url
             * @param kwargs
             * @return Models::Response
             */
            Models::Response delete_(const std::string &url, py::kwargs kwargs = {});

            /**
             * @brief HEAD request
             *
             * @param url
             * @param kwargs
             * @return Models::Response
             */
            Models::Response head(const std::string &url, py::kwargs kwargs = {});

            /**
             * @brief OPTIONS request
             *
             * @param url
             * @param kwargs
             * @return Models::Response
             */
            Models::Response options(const std::string &url, py::kwargs kwargs = {});


            /**
             * @brief Handles the __enter__ method of the Session class
             *
             * @return Session*
             */
            Session* __enter__();

            /**
             * @brief Handles python side of the __exit__ method
             *
             * @param exc_type
             * @param exc_value
             * @param traceback
             */
            void __exit__(const py::object &exc_type, const py::object &exc_value, const py::object &traceback);
        };

        // Callback function to write data received from libcurl
        size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output);

    } // namespace Sessions

} // namespace Reqboost

#endif // SESSION_H
