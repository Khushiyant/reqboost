/**
 * @file StatusCodes.h
 * @brief HTTP status code constants and functions.
 *
 * This file defines constants for HTTP status codes and provides functions to
 * work with them.
 */

#ifndef STATUSCODES_H
#define STATUSCODES_H

namespace Reqboost {

    /**
     * @brief Get the Http Status Codes object
     *
     * @return const std::map<int, std::vector<std::string>>&
     */
    const std::map<int, std::vector<std::string>> &getHttpStatusCodes();

    /**
     * @brief Get the Status Code object
     *
     * @param name
     * @return int
     */
    int getStatusCode(const std::string &name);
}  // namespace Reqboost

#endif  //STATUSCODEST_P
