/**
 * @file InternalUtility.h
 * @brief Internal utility functions and constants for the reqboost library.
 *
 * This file provides internal utility functions and constants for the `reqboost` library.
 */

#ifndef INTERNALUTILITY_H
#define INTERNALUTILITY_H

#include <regex>
#include <stdexcept>
#include <cassert>
#include <codecvt>

// #include "Exceptions.h"

namespace Reqboost
{
    namespace InternalUtility
    {

        const std::regex kValidHeaderNameReByte(R"(^[^:\s][^:\r\n]*$)");
        const std::regex kValidHeaderNameReStr(R"(^[^:\s][^:\r\n]*$)");
        const std::regex kValidHeaderValueReByte(R"(^\S[^\r\n]*$|^$)");
        const std::regex kValidHeaderValueReStr(R"(^\S[^\r\n]*$|^$)");

        /**
         * @brief Tuple of regular expressions for validating HTTP header names and values.
         *
         * This tuple contains regular expressions for validating HTTP header names and values.
         * The first element is a regular expression for validating header names, and the second element is a regular expression for validating header values.
         */
        const std::tuple<std::regex, std::regex> kHeaderValidatorsByte(kValidHeaderNameReByte, kValidHeaderValueReByte);
        /**
         * @brief Tuple of regular expressions for validating HTTP header names and values as bytes.
         *
         * This tuple contains regular expressions for validating HTTP header names and values as bytes.
         * The first element is a regular expression for validating header names, and the second element is a regular expression for validating header values.
         */
        const std::tuple<std::regex, std::regex> kHeaderValidatorsStr(kValidHeaderNameReStr, kValidHeaderValueReStr);
        
        /**
         * @brief Enum for string type
         * 
         */
        enum class StringType
        {
            Bytes,
            Str
        };

        /**
         * @brief Convert a string to a native string
         * 
         * @param str 
         * @param encoding 
         * @return std::string 
         */
        std::string ToNativeString(const std::string &str, const std::string &encoding);

        /**
         * @brief Check if a string contains only ASCII characters
         * 
         * @param u_string 
         * @return true 
         * @return false 
         */
        bool UnicodeIsAscii(const std::string &u_string);

    }
}
#endif // INTERNALUTILITY_H