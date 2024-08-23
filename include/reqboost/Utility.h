#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <curl/curl.h>
#include <Poco/URI.h>

#include "Models.h"

namespace Reqboost {
    namespace Utility{
        std::string urlencode(const std::string &decoded);
        std::string urldecode(const std::string &encoded);
        std::string urlunparse(const Models::ParsedURL &parsed);
        Models::ParsedURL urlsplit(const std::string &url);
    }
}
#endif // UTILITY_H