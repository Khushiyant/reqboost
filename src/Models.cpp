
#include <iostream>
#include <map>
#include <string>
#include <any>
#include <vector>
#include <utility>

#include "Models.h"
#include "Utility.h"
namespace Reqboost
{
    namespace Models
    {
        // Default constructor for Response
        Response::Response()
            : _content(""), status_code(0), headers(), url(""), history(), encoding(""), reason(""), cookies(), elapsed(""), request("") {}


        // Methods


        bool Response::is_redirect()
        {
            // Check if status code is in the range 300-399 and "Location" header is present
            return  (REDIRECT_STATI.find(status_code) != REDIRECT_STATI.end());
        }

        bool Response::is_permanent_redirect()
        {
            int movedCode = getStatusCode("moved");
            int permanentRedirectCode = getStatusCode("permanent_redirect");
            if (movedCode == -1 || permanentRedirectCode == -1) {
                // Handle the case where the status code is not found
                return false;
            }
            return  (status_code == movedCode || status_code == permanentRedirectCode);
        }

        void Response::raise_for_status()
        {
            std::string reason;
            if (std::is_same<decltype(reason), std::string>::value)
            {
                try
                {
                    reason = Utility::decode_utf8(this->reason);
                }
                catch(const Exceptions::ContentDecodingError &e)
                {
                    throw Exceptions::ContentDecodingError("Content decoding error: " + std::string(e.what()));
                }
            }
            else
            {
                reason = this->reason;
            }

            std::string http_error_message;
            if (this->status_code >= 400 && this->status_code < 500)
            {
                http_error_message = "Client error: " + reason + " for url: " + this->url;
            }
            else if (this->status_code >= 500 && this->status_code < 600)
            {
                http_error_message = "Server error: " + reason + " for url: " + this->url;
            }
            if (http_error_message != "")
                throw Exceptions::HTTPError(http_error_message);
        }


        std::string Response::text()
        {
            std::string content;

            if (this->_content == "") // guessing encoding
                return "";

            if (this->encoding == "")
                this->encoding = "utf-8";

            try
            {
                content = Utility::decode_utf8(this->_content);
            }
            catch(const std::exception& e)
            {
                throw Exceptions::ContentDecodingError("Content decoding error: " + std::string(e.what()));
            }

            return content;
        }

        std::map<std::string, std::map<std::string, std::string>> Response::links()
        {
            std::map<std::string, std::map<std::string, std::string>> resolved_links;

            auto header = headers.find("link");
            if (header != headers.end())
            {
                auto links = Utility::parse_header_links(header->second);

                for (const auto &link : links)
                {
                    std::string key;
                    if (link.find("rel") != link.end())
                    {
                        key = link.at("rel");
                    }
                    else if (link.find("url") != link.end())
                    {
                        key = link.at("url");
                    }

                    resolved_links[key] = link;
                }
            }

            return resolved_links;
        }

        // Dunder methods
        std::string Response::__repr__()
        {
            return "<Response [" + std::to_string(status_code) + "]>";
        }
        bool Response::__nonzero__()
        {
            return this->ok();
        }

        bool Response::__bool__()
        {
            return this->ok();
        }


        // property methods
        bool Response::ok()
        {
            try
            {
                Response::raise_for_status();
            }
            catch(const Exceptions::RequestException &e)
            {
                throw e;
                return false;
            }

            return true;

        }

    } // namespace Models
} // namespace Reqboost
