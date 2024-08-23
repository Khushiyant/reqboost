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
        Models::Response request(const std::string &method, const std::string &url)
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

        Models::Response get(const std::string &url)
        {
            return request("GET", url);
        }
    }
}
