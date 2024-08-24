#include "Models.h"

namespace Reqboost
{
    namespace Models
    {
        // Default constructor for Response
        Response::Response()
            : _content(""), status_code(0), headers(), url(""), history(), encoding(""), reason(""), cookies(), elapsed(""), request("") {}

    } // namespace Models
} // namespace Reqboost
