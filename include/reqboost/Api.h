#ifndef API_H
#define API_H

#include <string>
#include <curl/curl.h>

#include "Models.h"

namespace Reqboost
{
    namespace Api
    {
        Models::Response request(const std::string &method, const std::string &url, Models::RequestOptions options = {});
        Models::Response get(const std::string &url, const std::map<std::string, std::string> &params = {}, Models::RequestOptions kwargs = {});
        Models::Response post(const std::string &url, const std::map<std::string, std::string> &data = {}, Models::RequestOptions kwargs = {});
        Models::Response put(const std::string &url, const std::map<std::string, std::string> &data = {}, Models::RequestOptions kwargs = {});
        Models::Response patch(const std::string &url, const std::map<std::string, std::string> &data = {}, Models::RequestOptions kwargs = {});
        Models::Response remove(const std::string &url, Models::RequestOptions kwargs = {});
        Models::Response head(const std::string &url, Models::RequestOptions kwargs = {});
        Models::Response options(const std::string &url, Models::RequestOptions kwargs = {});
    }
}

#endif // API_H
