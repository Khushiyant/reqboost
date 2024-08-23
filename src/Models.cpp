#include "Models.h"

namespace Reqboost
{
    namespace Models
    {
        // Constructor for RequestOptions
        RequestOptions::RequestOptions(const std::map<std::string, std::string> &params, const std::map<std::string, std::string> &data)
            : params(params), data(data) {}

        // Default constructor for Response
        Response::Response()
            : _content(""), status_code(0), headers(), url(""), history(), encoding(""), reason(""), cookies(), elapsed(""), request("") {}

    } // namespace Models
} // namespace Reqboost
