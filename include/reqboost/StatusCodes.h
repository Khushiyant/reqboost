/**
 * @file StatusCodes.h
 * @brief HTTP status code constants and functions.
 *
 * This file defines constants for HTTP status codes and provides functions to
 * work with them.
 */

#ifndef STATUSCODES_H
#define STATUSCODES_H

#include <string>
#include <map>
#include <vector>
#include <iostream>

namespace Reqboost {
    /**
     * @brief map of HTTP status codes and their names
     * 
     */
    extern std::map<int, std::vector<std::string>> httpStatusCodes;

    /**
     * @brief Get the Status Code object
     * 
     * @param name 
     * @return int 
     */
    int getStatusCode(const std::string &name);
}  // namespace Reqboost

#endif  //STATUSCODEST_P