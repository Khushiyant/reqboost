#include "Models.h"
namespace Reqboost
{
    namespace Models
    {
        RequestEncodingMixin::RequestEncodingMixin(const std::string &u) : url(u) {}

        std::string RequestEncodingMixin::path_url() const
        {
            std::vector<std::string> url_parts;

            auto p = urlsplit(url); // Assume urlsplit is implemented somewhere
            std::string path = p.path;
            if (path.empty())
            {
                path = "/";
            }

            url_parts.push_back(path);

            std::string query = p.query;
            if (!query.empty())
            {
                url_parts.push_back("?");
                url_parts.push_back(query);
            }

            return join(url_parts, ""); // Assume join is implemented somewhere
        }

        std::string RequestEncodingMixin::_encode_params(const std::any &data)
        {
            if (data.type() == typeid(std::string) || data.type() == typeid(std::vector<char>))
            {
                return std::any_cast<std::string>(data);
            }
            else if (has_read_method(data))
            { // Assume has_read_method is implemented
                return std::any_cast<std::string>(data);
            }
            else if (is_iterable(data))
            { // Assume is_iterable is implemented
                std::vector<std::pair<std::string, std::string>> result;
                auto key_val_list = to_key_val_list(data);

                for (const auto &[k, vs] : key_val_list)
                {
                    std::vector<std::any> vs_list;
                    if (vs.type() == typeid(std::string) || !is_iterable(vs))
                    {
                        vs_list = {vs};
                    }
                    else
                    {
                        vs_list = std::any_cast<std::vector<std::any>>(vs);
                    }

                    for (const auto &v : vs_list)
                    {
                        if (v.has_value())
                        {
                            result.emplace_back(
                                (k.type() == typeid(std::string)) ? std::any_cast<std::string>(k) : std::string(),
                                (v.type() == typeid(std::string)) ? std::any_cast<std::string>(v) : std::string());
                        }
                    }
                }

                return Utility::urlencode(result, true); // Assume urlencode is implemented
            }
            else
            {
                return std::any_cast<std::string>(data);
            }
        }

        std::pair<std::string, std::string> RequestEncodingMixin::_encode_files(const std::any &files, const std::any &data)
        {
            if (!files.has_value())
            {
                throw std::invalid_argument("Files must be provided.");
            }
            else if (data.type() == typeid(std::string))
            {
                throw std::invalid_argument("Data must not be a string.");
            }

            std::vector<std::pair<std::string, std::string>> new_fields;
            auto fields = to_key_val_list(data);
            auto file_list = to_key_val_list(files);

            for (const auto &[field, val] : fields)
            {
                std::vector<std::any> val_list;
                if (val.type() == typeid(std::string) || !is_iterable(val))
                {
                    val_list = {val};
                }
                else
                {
                    val_list = std::any_cast<std::vector<std::any>>(val);
                }

                for (const auto &v : val_list)
                {
                    if (v.has_value())
                    {
                        std::string str_val = (v.type() == typeid(std::string)) ? std::any_cast<std::string>(v) : std::string();
                        new_fields.emplace_back(
                            (field.type() == typeid(std::string)) ? std::any_cast<std::string>(field) : std::string(),
                            str_val);
                    }
                }
            }

            for (const auto &[k, v] : file_list)
            {
                std::string fn, fdata;
                std::string ft;
                std::map<std::string, std::string> fh;

                if (v.type() == typeid(std::tuple<std::string, std::any>) || v.type() == typeid(std::tuple<std::string, std::any, std::string, std::map<std::string, std::string>>))
                {
                    auto file_tuple = std::any_cast<std::tuple<std::string, std::any>>(v);
                    fn = std::get<0>(file_tuple);
                    fdata = std::any_cast<std::string>(std::get<1>(file_tuple));
                    if constexpr (std::tuple_size<decltype(file_tuple)>::value > 2)
                    {
                        ft = std::get<2>(file_tuple);
                        fh = std::get<3>(file_tuple);
                    }
                }
                else
                {
                    fn = guess_filename(v) ? guess_filename(v) : std::any_cast<std::string>(k);
                    fdata = std::any_cast<std::string>(v);
                }

                RequestField rf(k, fdata, fn, fh); // Assume RequestField is implemented
                rf.make_multipart(ft);             // Assume make_multipart is implemented
                new_fields.push_back(std::make_pair(k, fdata));
            }

            auto [body, content_type] = encode_multipart_formdata(new_fields); // Assume encode_multipart_formdata is implemented

            return {body, content_type};
        }

        Response::Response() : _content(""), status_code(0), headers(), url(""), history(), encoding(""), reason(""), cookies(), elapsed(""), request("") {}
    } // namespace Models
} // namespace Reqboost
