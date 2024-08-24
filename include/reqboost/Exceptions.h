#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <exception>
#include <string>
namespace Reqboost{

    namespace Exceptions{
        // Base class for exceptions
        class RequestException : public virtual std::runtime_error
        {
        public:
            explicit RequestException(const std::string &message, const std::exception *response = nullptr, const std::exception *request = nullptr);
            RequestException() : std::runtime_error("") {}
            const char *what() const throw() override { return message_.c_str(); }

        private:
            const std::exception *response_;
            const std::exception *request_;

            const std::string message_;
        };

        // Derived exceptions
        class InvalidJSONError : public virtual RequestException
        {
        public:
            explicit InvalidJSONError(const std::string &message);
        };

        class JSONDecodeError : public InvalidJSONError
        {
        public:
            explicit JSONDecodeError(const std::string &message);
        };

        class HTTPError : public RequestException
        {
        public:
            explicit HTTPError(const std::string &message);
        };

        class ConnectionError : public virtual RequestException
        {
        public:
            explicit ConnectionError(const std::string &message);
        };

        class ProxyError : public ConnectionError
        {
        public:
            explicit ProxyError(const std::string &message);
        };

        class SSLError : public ConnectionError
        {
        public:
            explicit SSLError(const std::string &message);
        };

        class Timeout : public virtual RequestException
        {
        public:
            explicit Timeout(const std::string &message);
        };

        class ConnectTimeout : public ConnectionError, public Timeout
        {
        public:
            explicit ConnectTimeout(const std::string &message);
        };

        class ReadTimeout : public Timeout
        {
        public:
            explicit ReadTimeout(const std::string &message);
        };

        class URLRequired : public RequestException
        {
        public:
            explicit URLRequired(const std::string &message);
        };

        class TooManyRedirects : public RequestException
        {
        public:
            explicit TooManyRedirects(const std::string &message);
        };

        class MissingSchema : public RequestException, public std::invalid_argument
        {
        public:
            explicit MissingSchema(const std::string &message);

            const char *what() const throw() override { return "Missing schema"; }
        };

        class InvalidSchema : public RequestException, public std::invalid_argument
        {
        public:
            explicit InvalidSchema(const std::string &message);

            const char *what() const throw() override { return "Invalid schema"; }
        };

        class InvalidURL : public RequestException, public std::invalid_argument
        {
        public:
            explicit InvalidURL(const std::string &message);

            const char *what() const throw() override { return "Invalid URL"; }
        };

        class InvalidHeader : public RequestException, public std::invalid_argument
        {
        public:
            explicit InvalidHeader(const std::string &message);

            const char *what() const throw() override { return "Invalid header"; }
        };

        class InvalidProxyURL : public InvalidURL
        {
        public:
            explicit InvalidProxyURL(const std::string &message);

            const char *what() const throw() override { return "Invalid proxy URL"; }
        };

        class ChunkedEncodingError : public RequestException
        {
        public:
            explicit ChunkedEncodingError(const std::string &message);
        };

        class ContentDecodingError : public RequestException
        {
        public:
            explicit ContentDecodingError(const std::string &message);
        };

        class StreamConsumedError : public RequestException, public std::logic_error
        {
        public:
            explicit StreamConsumedError(const std::string &message);

            const char *what() const throw() override { return "Stream consumed"; }

        };

        class RetryError : public RequestException
        {
        public:
            explicit RetryError(const std::string &message);
        };

        class UnrewindableBodyError : public RequestException
        {
        public:
            explicit UnrewindableBodyError(const std::string &message);
        };

        // Warnings
        class RequestsWarning : public std::exception
        {
        public:
            explicit RequestsWarning(const std::string &message);
            const char *what() const throw()
            {
                return message_.c_str();
            }

        private:
            std::string message_;
        };

        class FileModeWarning : public RequestsWarning
        {
        public:
            
            explicit FileModeWarning(const std::string &message);
        };

        class RequestsDependencyWarning : public RequestsWarning
        {
        public:
            explicit RequestsDependencyWarning(const std::string &message);
        };
    }
}
#endif // EXCEPTIONS_H
