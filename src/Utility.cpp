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
    }
}