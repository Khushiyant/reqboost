#include <sstream>
#include <algorithm>
#include <random>

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
            : _content(""), status_code(0), headers(), url(""), history(), encoding(""), reason(""), cookies(), elapsed(std::chrono::duration<double>::zero()), request("") {}


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

        Exceptions::RequestException Response::raise_for_status()
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

        std::string Response::apparent_encoding()
        {
            return Utility::detect_encoding(this->_content,  this->_content.length());
        }

        std::string RequestEncodingMixin::path_url(const std::string &url)
        {
            ParsedURL p = urlsplit(url);
            std::stringstream urlStream;

            std::string path = p.path.empty() ? "/" : p.path;
            urlStream << path;

            if (!p.query.empty())
            {
                urlStream << "?" << p.query;
            }

            return urlStream.str();
        }

        std::string RequestEncodingMixin::encode_params(const std::map<std::string, std::string> &data)
        {
            std::stringstream result;

            for (const auto &pair : data)
            {
                if (!result.str().empty())
                {
                    result << "&";
                }
                result << pair.first << "=" << pair.second;
            }

            return result.str();
        }

        ParsedURL RequestEncodingMixin::urlsplit(const std::string &url)
        {
            ParsedURL parsed;
            size_t scheme_end = url.find("://");
            if (scheme_end != std::string::npos)
            {
                parsed.scheme = url.substr(0, scheme_end);
                size_t host_start = scheme_end + 3;
                size_t path_start = url.find("/", host_start);
                parsed.host = url.substr(host_start, path_start - host_start);
                parsed.path = url.substr(path_start);
            }
            return parsed;
        }

        void RequestHooksMixin::register_hook(const std::string &event, const std::function<void()> &hook)
        {
            hooks[event].push_back(hook);
        }

        bool RequestHooksMixin::deregister_hook(const std::string &event, const std::function<void()> &hook)
        {
            auto &event_hooks = hooks[event];
            auto it = std::remove_if(event_hooks.begin(), event_hooks.end(),
                                    [&hook](const std::function<void()> &stored_hook)
                                    {
                                        // Comparing the target of function objects
                                        return hook.target<void()>() == stored_hook.target<void()>();
                                    });

            if (it != event_hooks.end())
            {
                event_hooks.erase(it, event_hooks.end());
                return true;
            }
            return false;
        }

        MultipartEncoder::MultipartEncoder() {}

        std::pair<std::string, std::string> MultipartEncoder::encode_multipart_formdata(const std::map<std::string, std::string> &fields, const std::map<std::string, std::pair<std::string, std::string>> &files)
        {
            std::string boundary = generate_boundary();
            std::string body;
            std::string content_type = "multipart/form-data; boundary=" + boundary;

            for (const auto &field : fields)
            {
                body += create_form_field(field.first, field.second);
            }

            for (const auto &file : files)
            {
                body += create_file_field(file.first, file.second);
            }

            body += "--" + boundary + "--\r\n";
            return {body, content_type};
        }

        std::string MultipartEncoder::generate_boundary()
        {
            static const char alphanum[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
            int len = 30;
            std::string boundary;
            boundary.reserve(len);

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, sizeof(alphanum) - 2);

            for (int i = 0; i < len; ++i)
            {
                boundary += alphanum[dis(gen)];
            }

            return boundary;
        }

        std::string MultipartEncoder::create_form_field(const std::string &name, const std::string &value)
        {
            return "--" + generate_boundary() + "\r\n" +
                   "Content-Disposition: form-data; name=\"" + name + "\"\r\n\r\n" +
                   value + "\r\n";
        }

        std::string MultipartEncoder::create_file_field(const std::string &name, const std::pair<std::string, std::string> &file_info)
        {
            return "--" + generate_boundary() + "\r\n" +
                   "Content-Disposition: form-data; name=\"" + name + "\"; filename=\"" + file_info.first + "\"\r\n" +
                   "Content-Type: application/octet-stream\r\n\r\n" +
                   file_info.second + "\r\n";
        }

    } // namespace Models
} // namespace Reqboost
