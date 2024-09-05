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
