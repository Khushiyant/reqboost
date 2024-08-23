#ifndef MODELS_H
#define MODELS_H

#include <iostream>
#include <map>
#include <string>
#include <any>
#include <vector>
#include <utility>

namespace Reqboost
{
    namespace Models
    {
        struct ParsedURL
        {
            std::string scheme;
            std::string host;
            std::string path;
            std::string query;
            std::string fragment;
        };

        // Options

        struct RequestOptions {
            std::map<std::string, std::string> params = {};
            std::map<std::string, std::string> data = {};
        
            RequestOptions() = default;

            RequestOptions(const std::map<std::string, std::string> &params, const std::map<std::string, std::string> &data) : params(params), data(data) {}
        };


        // API Models
        class Response
        {
        public:
            std::string _content;
            int status_code;
            std::map<std::string, std::string> headers;
            std::string url;
            std::vector<Response> history;
            std::string encoding;
            std::string reason;
            std::map<std::string, std::string> cookies;

            std::string elapsed;
            std::string request;

            // Constructor
            Response();
        };
    } // namespace Models
} // namespace Reqboost

#endif // MODELS_H
