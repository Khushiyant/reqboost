#ifndef API_H
#define API_H

#include <string>
#include <curl/curl.h>

#include "Models.h"

namespace Reqboost
{
    namespace Api
    {
        Models::Response request(const std::string &method, const std::string &url);
        Models::Response get(const std::string &url);
    }
}

#endif // API_H
