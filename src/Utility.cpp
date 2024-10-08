#include <curl/curl.h>
#include <Poco/URI.h>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <codecvt>
#include <regex>
#include <map>

#include "Utility.h"

namespace Reqboost {
    namespace Utility {
        std::string detect_encoding(std::string _content_string, size_t _content_length)
        {
            const char *content = _content_string.c_str();
            size_t length = _content_length;

            // Check for UTF-8 BOM
            if (length >= 3 && content[0] == 0xEF && content[1] == 0xBB && content[2] == 0xBF)
            {
                return "utf-8";
            }

            // Check for utf-16 BOM
            if (length >= 2)
            {
                if (content[0] == 0xFE && content[1] == 0xFF)
                {
                    return "utf-16be";
                }
                if (content[0] == 0xFF && content[1] == 0xFE)
                {
                    return "utf-16le";
                }
            }

            // Simple UTF-8 validity check
            bool is_ascii = true;
            size_t i = 0;
            while (i < length)
            {
                if (content[i] <= 0x7F)
                {
                    i++;
                }
                else
                {
                    is_ascii = false;
                    if ((content[i] & 0xE0) == 0xC0)
                    {
                        if (i + 1 >= length || (content[i + 1] & 0xC0) != 0x80)
                            return "unknown";
                        i += 2;
                    }
                    else if ((content[i] & 0xF0) == 0xE0)
                    {
                        if (i + 2 >= length || (content[i + 1] & 0xC0) != 0x80 || (content[i + 2] & 0xC0) != 0x80)
                            return "unknown";
                        i += 3;
                    }
                    else if ((content[i] & 0xF8) == 0xF0)
                    {
                        if (i + 3 >= length || (content[i + 1] & 0xC0) != 0x80 || (content[i + 2] & 0xC0) != 0x80 || (content[i + 3] & 0xC0) != 0x80)
                            return "unknown";
                        i += 4;
                    }
                    else
                    {
                        return "unknown";
                    }
                }
            }

            return is_ascii ? "ascii" : "utf-8";
        }

        std::vector<std::map<std::string, std::string>> parse_header_links(const std::string &value)
        {
            std::vector<std::map<std::string, std::string>> links;

            std::string replace_chars = " '\"";

            std::string stripped_value = value;
            stripped_value.erase(0, stripped_value.find_first_not_of(replace_chars));
            stripped_value.erase(stripped_value.find_last_not_of(replace_chars) + 1);

            if (stripped_value.empty())
            {
                return links;
            }

            std::regex re(", *<");
            auto words_begin = std::sregex_token_iterator(stripped_value.begin(), stripped_value.end(), re, -1);
            auto words_end = std::sregex_token_iterator();

            for (std::sregex_token_iterator i = words_begin; i != words_end; ++i)
            {
                std::string val = *i;
                std::string url, params;

                size_t pos = val.find(";");
                if (pos != std::string::npos)
                {
                    url = val.substr(0, pos);
                    params = val.substr(pos + 1);
                }
                else
                {
                    url = val;
                    params = "";
                }

                std::map<std::string, std::string> link;
                link["url"] = url;
                link["url"].erase(0, link["url"].find_first_not_of("<> '\""));
                link["url"].erase(link["url"].find_last_not_of("<> '\"") + 1);

                size_t param_pos = 0;
                while ((param_pos = params.find(";")) != std::string::npos)
                {
                    std::string param = params.substr(0, param_pos);
                    size_t equal_pos = param.find("=");
                    if (equal_pos != std::string::npos)
                    {
                        std::string key = param.substr(0, equal_pos);
                        std::string value = param.substr(equal_pos + 1);
                        key.erase(0, key.find_first_not_of(replace_chars));
                        key.erase(key.find_last_not_of(replace_chars) + 1);
                        value.erase(0, value.find_first_not_of(replace_chars));
                        value.erase(value.find_last_not_of(replace_chars) + 1);
                        link[key] = value;
                    }
                    params.erase(0, param_pos + 1);
                }

                if (!params.empty())
                {
                    size_t equal_pos = params.find("=");
                    if (equal_pos != std::string::npos)
                    {
                        std::string key = params.substr(0, equal_pos);
                        std::string value = params.substr(equal_pos + 1);
                        key.erase(0, key.find_first_not_of(replace_chars));
                        key.erase(key.find_last_not_of(replace_chars) + 1);
                        value.erase(0, value.find_first_not_of(replace_chars));
                        value.erase(value.find_last_not_of(replace_chars) + 1);
                        link[key] = value;
                    }
                }

                links.push_back(link);
            }

            return links;
        }

        std::string decode_utf8(const std::string &encoded)
        {
            std::string result;
            const auto decoded_value = curl_easy_unescape(nullptr, encoded.c_str(), static_cast<int>(encoded.length()), nullptr);
            result = decoded_value;
            curl_free(decoded_value);
            return result;
        }
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
