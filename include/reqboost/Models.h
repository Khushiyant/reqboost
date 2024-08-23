#ifndef MODELS_H
#define MODELS_H

#include <iostream>
#include <map>
#include <string>
#include <any>
#include <vector>
#include <utility>

#include "Compat.h"

namespace Reqboost
{
    namespace Models
    {
        class RequestEncodingMixin
        {
        public:
            std::string url;

            // Constructor to set the URL
            RequestEncodingMixin(const std::string &u);

            // Method to build the path URL
            std::string path_url() const;

            // Static method to encode parameters in a piece of data
            static std::string _encode_params(const std::any &data);

            // Static method to build the body for a multipart/form-data request
            static std::pair<std::string, std::string> _encode_files(const std::any &files, const std::any &data);
        };

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
