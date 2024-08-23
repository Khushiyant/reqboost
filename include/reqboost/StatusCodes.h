#ifndef REQBOOST_HPP
#define REQBOOST_HPP

#include <string>
#include <map>
#include <vector>
#include <iostream>

namespace Reqboost {
    // Forward declaration of the httpStatusCodes map
    extern std::map<int, std::vector<std::string>> httpStatusCodes;

    // Function to get the HTTP status code from its name
    int getStatusCode(const std::string &name);
}  // namespace Reqboost

#endif  // REQBOOST_HPP