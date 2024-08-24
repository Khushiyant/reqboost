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

        // Regular expressions for header validation
        const std::regex kValidHeaderNameReByte(R"(^[^:\s][^:\r\n]*$)");
        const std::regex kValidHeaderNameReStr(R"(^[^:\s][^:\r\n]*$)");
        const std::regex kValidHeaderValueReByte(R"(^\S[^\r\n]*$|^$)");
        const std::regex kValidHeaderValueReStr(R"(^\S[^\r\n]*$|^$)");

        // Header validators map
        enum class StringType
        {
            Bytes,
            Str
        };

        const std::tuple<std::regex, std::regex> kHeaderValidatorsByte(kValidHeaderNameReByte, kValidHeaderValueReByte);

        const std::tuple<std::regex, std::regex> kHeaderValidatorsStr(kValidHeaderNameReStr, kValidHeaderValueReStr);

        // Function to convert to native string representation
        std::string ToNativeString(const std::string &str, const std::string &encoding);

        // Function to check if a string contains only ASCII characters
        bool UnicodeIsAscii(const std::string &u_string);

    }
}
#endif // INTERNALUTILITY_H