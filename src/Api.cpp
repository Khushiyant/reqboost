#include "Api.h"

// Callback function to write data received from libcurl
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output)
{
    size_t total_size = size * nmemb;
    output->append(static_cast<char *>(contents), total_size);
    return total_size;
}

namespace Reqboost
{
    namespace Api
    {

        Models::Response request(const std::string &method, const std::string &url, Models::RequestOptions options)
        {

            Models::Response response;
            CURL *curl = curl_easy_init();
            if (curl)
            {
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response._content);
                curl_easy_perform(curl);
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.status_code);
                curl_easy_cleanup(curl);
            }
            return response;
        }

        Models::Response get(const std::string &url, const std::map<std::string, std::string> &params, Models::RequestOptions kwargs)
        {
            kwargs.params = params;
            return request("GET", url, kwargs);
        }

        Models::Response post(const std::string &url, const std::map<std::string, std::string> &data, Models::RequestOptions kwargs)
        {
            kwargs.data = data;
            return request("POST", url, kwargs);
        }

        Models::Response put(const std::string &url, const std::map<std::string, std::string> &data, Models::RequestOptions kwargs)
        {
            kwargs.data = data;
            return request("PUT", url, kwargs);
        }

        Models::Response remove(const std::string &url, Models::RequestOptions kwargs)
        {
            return request("DELETE", url, kwargs);
        }

        Models::Response head(const std::string &url, Models::RequestOptions kwargs)
        {
            return request("HEAD", url, kwargs);
        }

        Models::Response patch(const std::string &url, const std::map<std::string, std::string> &data, Models::RequestOptions kwargs)
        {
            kwargs.data = data;
            return request("PATCH", url, kwargs);
        }

        Models::Response options(const std::string &url, Models::RequestOptions kwargs)
        {
            return request("OPTIONS", url, kwargs);
        }


    }
}
