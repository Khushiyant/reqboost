#ifndef UTILITY_H
#define UTILITY_H

#include <string>
namespace Reqboost {
    namespace Utility{
        std::string url_encode(const std::string &decoded);
        std::string url_decode(const std::string &encoded);
    }
}
#endif // UTILITY_H