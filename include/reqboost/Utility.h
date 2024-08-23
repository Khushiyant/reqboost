#ifndef UTILITY_H
#define UTILITY_H

#include <string>
namespace Reqboost {
    namespace Utility{
        std::string urlencode(const std::string &decoded);
        std::string urldecode(const std::string &encoded);
    }
}
#endif // UTILITY_H