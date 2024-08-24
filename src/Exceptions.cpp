#include "Exceptions.h"

namespace Reqboost{
    namespace Exceptions{
        // Base class implementation

        RequestException::RequestException(const std::string &message, const std::exception *response, const std::exception *request)
            : std::runtime_error(message), response_(response), request_(request), message_(message)
        {
            if (response != nullptr && request == nullptr && response != this)
            {
                this->request_ = response;
            }
        }

        // Derived class implementations
        InvalidJSONError::InvalidJSONError(const std::string &message)
            : std::runtime_error(message), RequestException(message) {}

        JSONDecodeError::JSONDecodeError(const std::string &message)
            : std::runtime_error(message), InvalidJSONError(message) {}
        HTTPError::HTTPError(const std::string &message)
            : std::runtime_error(message), RequestException(message) {}

        ConnectionError::ConnectionError(const std::string &message)
            : std::runtime_error(message), RequestException(message) {}

        ProxyError::ProxyError(const std::string &message)
            : std::runtime_error(message), ConnectionError(message) {}

        SSLError::SSLError(const std::string &message)
            : std::runtime_error(message), ConnectionError(message) {}

        Timeout::Timeout(const std::string &message)
            : std::runtime_error(message), RequestException(message) {}

        ConnectTimeout::ConnectTimeout(const std::string &message)
            : std::runtime_error(message), ConnectionError(message), Timeout(message) {}

        ReadTimeout::ReadTimeout(const std::string &message)
            : std::runtime_error(message), Timeout(message) {}

        URLRequired::URLRequired(const std::string &message)
            : std::runtime_error(message), RequestException(message) {}

        TooManyRedirects::TooManyRedirects(const std::string &message)
            : std::runtime_error(message), RequestException(message) {}

        MissingSchema::MissingSchema(const std::string &message)
            : std::runtime_error(message), RequestException(message), std::invalid_argument(message) {}

        InvalidSchema::InvalidSchema(const std::string &message)
            : std::runtime_error(message), RequestException(message), std::invalid_argument(message) {}

        InvalidURL::InvalidURL(const std::string &message)
            : std::runtime_error(message), RequestException(message), std::invalid_argument(message) {}

        InvalidHeader::InvalidHeader(const std::string &message)
            : std::runtime_error(message), RequestException(message), std::invalid_argument(message) {}

        InvalidProxyURL::InvalidProxyURL(const std::string &message)
            : std::runtime_error(message), InvalidURL(message) {}

        ChunkedEncodingError::ChunkedEncodingError(const std::string &message)
            : std::runtime_error(message), RequestException(message) {}

        ContentDecodingError::ContentDecodingError(const std::string &message)
            : std::runtime_error(message), RequestException(message) {}

        StreamConsumedError::StreamConsumedError(const std::string &message)
            : std::runtime_error(message), RequestException(message), std::logic_error(message) {}

        RetryError::RetryError(const std::string &message)
            : std::runtime_error(message), RequestException(message) {}

        UnrewindableBodyError::UnrewindableBodyError(const std::string &message)
            : std::runtime_error(message), RequestException(message) {}

        // Warnings
        RequestsWarning::RequestsWarning(const std::string &message)
            : std::exception(), message_(message) {}

        FileModeWarning::FileModeWarning(const std::string &message)
            : RequestsWarning(message) {}

        RequestsDependencyWarning::RequestsDependencyWarning(const std::string &message)
            : RequestsWarning(message) {}
    }
}