#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <elasticpp/json.hpp>
using json = nlohmann::json;

namespace elasticpp {

enum ELASTICPP_CURL_CMD {
  POST, PUT, GET, DELETE
};

void elastic_cpp_curl_cleanup();

void elastic_cpp_curl_init(const std::string& _credentials,
                           const std::string& _caCertFilepath,
                           const std::string& _caPass);

std::string elastic_cpp(const std::string& _url,
                        const std::string& _credentials,
                        const std::string& _caCertFilepath,
                        const std::string& _caPass,
                        const std::string& _message,
                        ELASTICPP_CURL_CMD _cmdType = POST, bool _singleCall = false, int _verbose = 0);
json elastic_cpp(const std::string& _url,
                 const std::string& _credentials,
                 const std::string& _caCertFilepath,
                 const std::string& _caPass,
                 const json& _message,
                 ELASTICPP_CURL_CMD _cmdType = POST, bool _singleCall = false, int _verbose = 0);

} // namespace elasticpp
