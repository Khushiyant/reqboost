#include "Utility.h"

namespace Reqboost {
    namespace Utility {

        std::string urlunparse(const Models::ParsedURL &parsed)
        {
            Poco::URI uri;

            uri.setScheme(parsed.scheme);
            uri.setHost(parsed.host);
            uri.setPath(parsed.path);
            uri.setQuery(parsed.query);
            uri.setFragment(parsed.fragment);

            return uri.toString();
        }
        std::string urlencode(const std::string &decoded)
        {
            const auto encoded_value = curl_easy_escape(nullptr, decoded.c_str(), static_cast<int>(decoded.length()));
            std::string result(encoded_value);
            curl_free(encoded_value);
            return result;
        }

        std::string urldecode(const std::string &encoded)
        {
            int output_length;
            const auto decoded_value = curl_easy_unescape(nullptr, encoded.c_str(), static_cast<int>(encoded.length()), &output_length);
            std::string result(decoded_value, output_length);
            curl_free(decoded_value);
            return result;
        }

        Models::ParsedURL urlsplit(const std::string &url)
        {
            Poco::URI uri(url);

            Models::ParsedURL parsed;
            parsed.scheme = uri.getScheme();
            parsed.host = uri.getHost();
            parsed.path = uri.getPath();
            parsed.query = uri.getQuery();
            parsed.fragment = uri.getFragment();

            return parsed;
        }

        // LogMessage class definitions
        LogMessage::LogMessage(LogLevel level, const std::string &message)
            : level(level), message(message) {}

        LogLevel LogMessage::getLevel() const
        {
            return level;
        }

        std::string LogMessage::getMessage() const
        {
            return message;
        }

        // ConsoleSink class definition
        void ConsoleSink::log(const LogMessage &message)
        {
            std::cout << message.getMessage() << std::endl;
        }

        // FileSink class definitions
        FileSink::FileSink(const std::string &filename) : file(filename, std::ios::app) {}

        void FileSink::log(const LogMessage &message)
        {
            file << message.getMessage() << std::endl;
        }

        // Logger class definitions
        void Logger::addSink(std::shared_ptr<LogSink> sink)
        {
            sinks.push_back(sink);
        }

        void Logger::log(LogLevel level, const std::string &message)
        {
            LogMessage logMessage(level, message);
            for (const auto &sink : sinks)
            {
                sink->log(logMessage);
            }
        }
    }
}