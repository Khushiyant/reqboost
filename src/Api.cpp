#include "Api.h"
#include <curl/curl.h>

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
        std::string get(const std::string &url)
        {
            CURL *curl = curl_easy_init(); // Initialize a CURL session
            if (!curl)
            {
                return ""; // Return empty string if initialization failed
            }

            std::string result; // String to hold the result
            CURLcode res;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());             // Set URL
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // Set write callback
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);           // Set data buffer

            res = curl_easy_perform(curl); // Perform the request
            if (res != CURLE_OK)
            {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                result.clear(); // Clear result on failure
            }

            curl_easy_cleanup(curl); // Clean up CURL session
            return result;           // Return the result
        }
    }
}
