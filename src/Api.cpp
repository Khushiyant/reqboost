#include "Api.h"


namespace Reqboost
{
    namespace Api
    {

        Models::Response request(const std::string &method, const std::string &url, const py::kwargs kwargs)
        {
            Sessions::Session session;

            return session.request(method, url, kwargs);
        }

        Models::Response get(const std::string &url, const py::dict params, py::kwargs kwargs)
        {
            kwargs["params"] = params;
            return request("GET", url, kwargs);
        }

        Models::Response post(const std::string &url, const py::dict data, py::kwargs kwargs)
        {
            kwargs["data"] = data;
            return request("POST", url, kwargs);
        }

        Models::Response put(const std::string &url, const py::dict data, py::kwargs kwargs)
        {
            kwargs["data"] = data;
            return request("PUT", url, kwargs);
        }

        Models::Response delete_(const std::string &url, py::kwargs kwargs)
        {
            return request("DELETE", url, kwargs);
        }

        Models::Response head(const std::string &url, py::kwargs kwargs)
        {
            return request("HEAD", url, kwargs);
        }

        Models::Response patch(const std::string &url, const py::dict data, py::kwargs kwargs)
        {
            kwargs["data"] = data;
            return request("PATCH", url, kwargs);
        }

        Models::Response options(const std::string &url, py::kwargs kwargs)
        {
            return request("OPTIONS", url, kwargs);
        }

    }
}
