#include <elasticpp/ElastiCpp.h>

namespace elasticpp {


ElastiCpp::ElastiCpp(const std::string& _baseUrl, const std::string& _credentials) :
    baseUrl_(_baseUrl),
    credentials_(_credentials) {
  elastic_cpp_curl_init(credentials_);
}

ElastiCpp::~ElastiCpp() {

}

bool ElastiCpp::createIndex(const std::string& _index, int _shards, int _replicas,
    int _verbose) const {
  const json response = elastic_cpp(baseUrl_ + _index, credentials_, json(),
      PUT, false, _verbose);

#ifndef NDEBUG
  if ( _verbose > 0) {
    std::cout << "response: " << response.dump(3) << std::endl;
  }
#endif // NDEBUG

  if ( response.count("acknowledged") ) {
    return response["acknowledged"].get<bool>();
  }

  return false;
}

bool ElastiCpp::deleteIndex(const std::string& _index, int _verbose) const {
  const json response = elastic_cpp(baseUrl_ + _index, credentials_, json(),
      DELETE, false, _verbose);

#ifndef NDEBUG
  if ( _verbose > 0) {
    std::cout << "response: " << response.dump(3) << std::endl;
  }
#endif // NDEBUG

  if ( response.count("acknowledged") ) {
    return response["acknowledged"].get<bool>();
  }

  return false;
}

json ElastiCpp::getIndex(const std::string& _index, int _verbose) const {
  return elastic_cpp(baseUrl_ + _index, credentials_, json(),
      GET, false, _verbose);
}

json ElastiCpp::send(const std::string& _url, const json& _message, ELASTICPP_CURL_CMD _cmdType,
    int _verbose) const {
  return elastic_cpp(baseUrl_ + _url, credentials_, _message,
      _cmdType, false, _verbose);
}

} // namespace elasticpp
