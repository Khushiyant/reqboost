#ifndef COMPAT_H
#define COMPAT_H

#include <string>
#include <string>
#include <curl/curl.h>

namespace Reqboost
{
    namespace Compat
    {
        std::string urlencode(const std::string &decoded);
        std::string urldecode(const std::string &encoded);
    }
}
#endif // COMPAT_H