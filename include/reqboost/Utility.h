#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <curl/curl.h>
#include <Poco/URI.h>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <codecvt>
#include <regex>
#include "Models.h"

namespace Reqboost {
    namespace Utility{
       /**
        * @brief Parse a header links string into a vector of maps.
        *
        * This function takes a string representing a header links value and
        * parses it into a vector of maps, where each map represents a link.
        *
        * @param value The header links string to parse.
        * @return A vector of maps, where each map represents a link.
        */
       std::vector<std::map<std::string, std::string>> parse_header_links(std::string value);
       
       /**
        * @brief Decode a UTF-8 encoded string.
        *
        * This function takes a UTF-8 encoded string and decodes it into a
        * regular string.
        *
        * @param encoded The UTF-8 encoded string to decode.
        * @return The decoded string.
        */
       std::string decode_utf8(const std::string &encoded);
       
       /**
        * @brief URL encode a string.
        *
        * This function takes a string and URL encodes it, replacing special
        * characters with their corresponding escape sequences.
        *
        * @param decoded The string to URL encode.
        * @return The URL encoded string.
        */
       std::string urlencode(const std::string &decoded);
       
       /**
        * @brief URL decode a string.
        *
        * This function takes a URL encoded string and decodes it, replacing
        * escape sequences with their corresponding special characters.
        *
        * @param encoded The URL encoded string to decode.
        * @return The decoded string.
        */
       std::string urldecode(const std::string &encoded);
       
       /**
        * @brief Unparse a ParsedURL object into a URL string.
        *
        * This function takes a ParsedURL object and unparse it into a URL
        * string.
        *
        * @param parsed The ParsedURL object to unparse.
        * @return The URL string.
        */
       std::string urlunparse(const Models::ParsedURL &parsed);
       
       /**
        * @brief Split a URL into its components.
        *
        * This function takes a URL string and splits it into its components,
        * returning a ParsedURL object.
        *
        * @param url The URL string to split.
        * @return A ParsedURL object representing the URL components.
        */
       Models::ParsedURL urlsplit(const std::string &url);

        enum LogLevel
        {
            INFO,
            WARNING,
            ERROR
        };

        // LogMessage class declaration
        class LogMessage
        {
        public:
            LogMessage(LogLevel level, const std::string &message);
            LogLevel getLevel() const;
            std::string getMessage() const;

        private:
            LogLevel level;
            std::string message;
        };

        // LogSink interface declaration
        class LogSink
        {
        public:
            virtual void log(const LogMessage &message) = 0;
            virtual ~LogSink() = default;
        };

        // ConsoleSink class declaration
        class ConsoleSink : public LogSink
        {
        public:
            void log(const LogMessage &message) override;
        };

        // FileSink class declaration
        class FileSink : public LogSink
        {
        public:
            FileSink(const std::string &filename);
            void log(const LogMessage &message) override;

        private:
            std::ofstream file;
        };

        // Logger class declaration
        class Logger
        {
        public:
            void addSink(std::shared_ptr<LogSink> sink);
            void log(LogLevel level, const std::string &message);

        private:
            std::vector<std::shared_ptr<LogSink>> sinks;
        };
    }
}
#endif // UTILITY_H
