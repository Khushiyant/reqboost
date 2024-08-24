#include "InternalUtility.h"
#include <iostream>

namespace Reqboost
{
    namespace InternalUtility {

        // Function to convert to native string representation
        std::string ToNativeString(const std::string &str, const std::string &encoding)
        {
            if (encoding == "utf-8")
            {
                // Convert std::string to std::wstring
                std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
                std::wstring wstr(str.begin(), str.end());

                // Use codecvt to convert from UTF-8 to native string
                return converter.to_bytes(wstr);
            }
            else if (encoding == "ascii")
            {
                return str;
            }
            else
            {
                // throw Exceptions::ContentDecodingError("Unknown encoding: " + encoding);
            }

            return "";
        }

        // Function to check if a string contains only ASCII characters
        bool UnicodeIsAscii(const std::string &u_string)
        {
            try
            {
                // Check if all characters are in ASCII range
                for (char c : u_string)
                {
                    if (static_cast<unsigned char>(c) > 127)
                    {
                        return false;
                    }
                }
                return true;
            }
            catch (const std::exception &)
            {
                return false;
            }
        }
    } // namespace InternalUtility

} // namespace Reqboost