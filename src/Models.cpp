#include "Models.h"

namespace Reqboost
{
    namespace Models
    {
        // Default constructor for Response
        Response::Response()
            : _content(""), status_code(0), headers(), url(""), history(), encoding(""), reason(""), cookies(), elapsed(""), request("") {}

        std::string Response::__repr__()
        {
            return "<Response [" + std::to_string(status_code) + "]>";
        }

        bool Response::ok() const
        {
            if (Response::status_code >= 200 && Response::status_code < 400)
            {
                return true;
            }
            else
            {
                throw Exceptions::HTTPError("Request failed with status code " + std::to_string(Response::status_code));
            }
        }

    } // namespace Models
} // namespace Reqboost
