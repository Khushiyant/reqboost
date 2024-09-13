#ifndef MODELS_H
#define MODELS_H

#include <iostream>
#include <map>
#include <string>
#include <any>
#include <vector>
#include <utility>
#include <unordered_set>

#include "Exceptions.h"
#include "StatusCodes.h"


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
                std::string _content;
                int status_code;
                std::map<std::string, std::string> headers ;
                std::string url;
                std::vector<Response> history;
                std::string encoding;
                std::string reason;
                std::map<std::string, std::string> cookies;

                std::string elapsed;
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

                // Constructor
                Response();
        };
    } // namespace Models
} // namespace Reqboost

#endif // MODELS_H
