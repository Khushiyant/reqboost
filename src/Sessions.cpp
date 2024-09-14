#include <string>

#include "Sessions.h"

namespace Reqboost
{
    namespace Sessions
    {
        Session::Session()
        {
            curl = curl_easy_init();
        }

        Session::~Session()
        {
            if (curl)
            {
                curl_easy_cleanup(curl);
                curl = nullptr;
            }
        }

        Session * Session::__enter__()
        {
            return this;
        }
        void Session::__exit__(const py::object &exc_type, const py::object &exc_value, const py::object &traceback)
        {
            // Cleanup and close the session
            if (curl)
            {
                curl_easy_cleanup(curl);
                curl = nullptr;
            }
        }

        Models::Response Session::request(const std::string &method, const std::string &url, const py::kwargs kwargs)
        {
            Models::Response response;

            if(curl)
            {
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response._content);
                curl_easy_perform(curl);
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.status_code);
            }

            return response;
        }

        Models::Response Session::get(const std::string &url, const py::dict params, py::kwargs kwargs)
        {
            kwargs["params"] = params;
            return Session::request("GET", url, kwargs);
        }

        Models::Response Session::post(const std::string &url, const py::dict data, py::kwargs kwargs)
        {
            kwargs["data"] = data;
            return Session::request("POST", url, kwargs);
        }

        Models::Response Session::put(const std::string &url, const py::dict data, py::kwargs kwargs)
        {
            kwargs["data"] = data;
            return Session::request("PUT", url, kwargs);
        }

        Models::Response Session::delete_(const std::string &url, py::kwargs kwargs)
        {
            return request("DELETE", url, kwargs);
        }

        Models::Response Session::head(const std::string &url, py::kwargs kwargs)
        {
            return Session::request("HEAD", url, kwargs);
        }

        Models::Response Session::patch(const std::string &url, const py::dict data, py::kwargs kwargs)
        {
            kwargs["data"] = data;
            return Session::request("PATCH", url, kwargs);
        }

        Models::Response Session::options(const std::string &url, py::kwargs kwargs)
        {
            return Session::request("OPTIONS", url, kwargs);
        }

        // Callback function to write data received from libcurl
        size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output)
        {
            size_t total_size = size * nmemb;
            output->append(static_cast<char *>(contents), total_size);
            return total_size;
        }
    }
}
