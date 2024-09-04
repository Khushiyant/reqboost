/**
 * @file Api.h
 * @brief This file contains the Reqboost::Api namespace, which provides a high-level API for making HTTP requests.
 *
 * This file includes the Reqboost::Api namespace, which provides a high-level API for making HTTP requests. It includes functions for making GET, POST, PUT, PATCH, and DELETE requests, as well as a generic request function.
 *
 * @see Api.cpp for the implementation of this API.
 */

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
        /**
         * @brief Makes a generic HTTP request.
         *
         * This function makes an HTTP request using the specified method and URL. It can also accept optional parameters and keyword arguments.
         *
         * @param method The HTTP method to use for the request.
         * @param url The URL to send the request to.
         * @param kwargs Optional keyword arguments for the request.
         * @return A Reqboost::Models::Response object containing the response from the server.
         */

        Models::Response request(const std::string &method, const std::string &url, const py::kwargs kwargs);
        /**
         * @brief Makes a GET request to the specified URL.
         *
         * This function makes a GET request to the specified URL. It can also accept optional parameters and keyword arguments.
         *
         * @param url The URL to send the request to.
         * @param params Optional parameters for the request.
         * @param kwargs Optional keyword arguments for the request.
         * @return A Reqboost::Models::Response object containing the response from the server.
         */
        Models::Response get(const std::string &url, const py::dict params = py::none(), py::kwargs kwargs = {});

        /**
         * @brief Makes a POST request to the specified URL.
         *
         * This function makes a POST request to the specified URL. It can also accept optional data and keyword arguments.
         *
         * @param url The URL to send the request to.
         * @param data Optional data for the request.
         * @param kwargs Optional keyword arguments for the request.
         * @return A Reqboost::Models::Response object containing the response from the server.
         */
        Models::Response post(const std::string &url, const py::dict data = py::none(), py::kwargs kwargs = {});

        /**
         * @brief Makes a PUT request to the specified URL.
         *
         * This function makes a PUT request to the specified URL. It can also accept optional data and keyword arguments.
         *
         * @param url The URL to send the request to.
         * @param data Optional data for the request.
         * @param kwargs Optional keyword arguments for the request.
         * @return A Reqboost::Models::Response object containing the response from the server.
         */
        Models::Response put(const std::string &url, const py::dict data = py::none(), py::kwargs kwargs = {});

        /**
         * @brief Makes a PATCH request to the specified URL.
         *
         * This function makes a PATCH request to the specified URL. It can also accept optional data and keyword arguments.
         *
         * @param url The URL to send the request to.
         * @param data Optional data for the request.
         * @param kwargs Optional keyword arguments for the request.
         * @return A Reqboost::Models::Response object containing the response from the server.
         */
        Models::Response patch(const std::string &url, const py::dict data = py::none(), py::kwargs kwargs = {});

        /**
         * @brief Makes a DELETE request to the specified URL.
         *
         * This function makes a DELETE request to the specified URL. It can also accept optional parameters and keyword arguments.
         *
         * @param url The URL to send the request to.
         * @param params Optional parameters for the request.
         * @param kwargs Optional keyword arguments for the request.
         * @return A Reqboost::Models::Response object containing the response from the server.
         */
        Models::Response delete_(const std::string &url, const py::dict params = py::none(), py::kwargs kwargs = {});
        
        /**
         * @brief Makes a HEAD request to the specified URL.
         *
         * This function makes a HEAD request to the specified URL. It can also accept optional parameters and keyword arguments.
         *
         * @param url The URL to send the request to.
         * @param params Optional parameters for the request.
         * @param kwargs Optional keyword arguments for the request.
         * @return A Reqboost::Models::Response object containing the response from the server.
         */
        Models::Response head(const std::string &url, const py::dict params = py::none(), py::kwargs kwargs = {});
        
        
        /**
         * @brief Makes an OPTIONS request to the specified URL.
         *
         * This function makes an OPTIONS request to the specified URL. It can also accept optional parameters and keyword arguments.
         *
         * @param url The URL to send the request to.
         * @param params Optional parameters for the request.
         * @param kwargs Optional keyword arguments for the request.
         * @return A Reqboost::Models::Response object containing the response from the server.
         */
        Models::Response options(const std::string &url, const py::dict params = py::none(), py::kwargs kwargs = {});
    }
}

#endif // API_H
