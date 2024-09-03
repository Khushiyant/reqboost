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

#include "Models.h"

namespace Reqboost {
    namespace Utility{
        std::string decode_utf8(const std::string &encoded);
        std::string urlencode(const std::string &decoded);
        std::string urldecode(const std::string &encoded);
        std::string urlunparse(const Models::ParsedURL &parsed);
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