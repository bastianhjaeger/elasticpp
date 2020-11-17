#pragma once

#include <elasticpp/elasticpp.h>

namespace elasticpp {

class ElastiCpp {
  friend class ElastiCppTest;
public:
  ElastiCpp(const std::string& _baseUrl, const std::string& _credentials = "");
  ~ElastiCpp();

  bool createIndex(const std::string& _index, int _shards = 1, int _replicas = 1, int _verbose = 0) const;
  bool deleteIndex(const std::string& _index, int _verbose = 0) const;
  json getIndex(const std::string& _index, int _verbose = 0) const;

  json send(const std::string& _url, const json& _message, ELASTICPP_CURL_CMD _cmdType = POST,
      int _verbose = 0) const;

private:
  const std::string baseUrl_; // e.g. "http://mydomain.com:9200/"
  const std::string credentials_; // e.g. "elastic:awesomepassword"
};

} // namespace elasticpp
