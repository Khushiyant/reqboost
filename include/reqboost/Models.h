#ifndef MODELS_H
#define MODELS_H

#include <unordered_set>

#include "Exceptions.h"
#include "StatusCodes.h"
#include <iostream>
#include <map>
#include <string>
#include <any>
#include <vector>
#include <utility>
#include <functional>

namespace Reqboost
{
    namespace Models
    {
        const std::unordered_set<int> REDIRECT_STATI = {
            getStatusCode("moved"),
            getStatusCode("found"),
            getStatusCode("see_other"),
            getStatusCode("not_modified"),
            getStatusCode("use_proxy"),
            getStatusCode("switch_proxy"),
            getStatusCode("temporary_redirect"),
            getStatusCode("permanent_redirect")};

        struct ParsedURL
        {
            std::string scheme;
            std::string host;
            std::string path;
            std::string query;
            std::string fragment;
        };

        // Options

        struct RequestOptions
        {
            std::map<std::string, std::string> params = {};
            std::map<std::string, std::string> data = {};

            RequestOptions() = default;

            RequestOptions(const std::map<std::string, std::string> &params, const std::map<std::string, std::string> &data) : params(params), data(data) {}
        };

        // API Models
        class Response
        {
            public:
                int status_code;

                std::string _content;
                std::map<std::string, std::string> headers ;
                std::string url;
                std::vector<Response> history;
                std::string encoding;
                std::string reason;
                std::map<std::string, std::string> cookies;

                // Sets the elapsed time of the request
                std::chrono::duration<double> elapsed;

                std::string request;

                // Methods
                /**
                 * @brief True if this Response is a well-formed HTTP redirect that could have been processed automatically (by :meth:`Session.resolve_redirects`)
                 *
                 * @return true
                 * @return false
                 */
                bool is_redirect();

                /**
                 * @brief True if this Response one of the permanent versions of redirect.
                 *
                 * @return true
                 * @return false
                 */
                bool is_permanent_redirect();

                /**
                 * @brief Raise an exception for status codes
                 *
                 */
                void raise_for_status();
                /**
                 * @brief Content of the response in unicode
                 *
                 * @return std::string
                 */
                std::string text();

                std::map<std::string, std::map<std::string, std::string>> links();

                // Dunder methods
                std::string __repr__();

                /**
                 * @brief Returns True if :attr:`status_code` is less than 400
                 *
                 * @return true
                 * @return false
                 */
                bool __nonzero__();

                /**
                 * @brief Returns True if :attr:`status_code` is less than 400.
                 *
                 * @return true
                 * @return false
                 */
                bool __bool__();

                // property methods
                bool ok() ;
                std::string apparent_encoding();

                // Constructor
                Response();
        };

        class RequestEncodingMixin
        {
            public:
                std::string path_url(const std::string &url);
                std::string encode_params(const std::map<std::string, std::string> &data);

            private:
                ParsedURL urlsplit(const std::string &url);    
        };
        
        class RequestHooksMixin
        {
        public:
            void register_hook(const std::string &event, const std::function<void()> &hook);
            bool deregister_hook(const std::string &event, const std::function<void()> &hook);

        private:
            std::map<std::string, std::vector<std::function<void()>>> hooks;
        };

        class MultipartEncoder
        {
        public:
            MultipartEncoder();
            std::pair<std::string, std::string> encode_multipart_formdata(const std::map<std::string, std::string> &fields, const std::map<std::string, std::pair<std::string, std::string>> &files);

        private:
            std::string generate_boundary();
            std::string create_form_field(const std::string &name, const std::string &value);
            std::string create_file_field(const std::string &name, const std::pair<std::string, std::string> &file_info);
        };
    } // namespace Models
} // namespace Reqboost

#endif // MODELS_H
