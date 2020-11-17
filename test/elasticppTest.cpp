#include <elasticpp/ElastiCpp.h>

#include <thread>
#include <chrono>

#include <gtest/gtest.h>

using namespace elasticpp;

const std::string TEST_URI = "http://localhost:9200/";
const std::string TEST_CRED = "user:password";


TEST(elasticppTest, elasticCpp_noHost) {
  json jResponse;
  std::string sResponse;

  EXPECT_NO_THROW( jResponse = elastic_cpp("", "", json(),
      POST, true, false) );
  EXPECT_NO_THROW( sResponse = elastic_cpp("", "", std::string(),
      POST, true, false) );

  std::cout << jResponse.dump(3) << std::endl;
  std::cout << sResponse << std::endl;
}

TEST(elasticppTest, elasticCpp_wrongHost) {
  json jResponse;
  std::string sResponse;

  EXPECT_NO_THROW( jResponse = elastic_cpp("http://localhostFoo:1234/test", "", json(),
      POST, true, false) );
  EXPECT_NO_THROW( sResponse = elastic_cpp("http://localhostFoo:1234/test", "", std::string(),
      POST, true, false) );

  std::cout << jResponse.dump(3) << std::endl;
  std::cout << sResponse << std::endl;
}


TEST(elasticppTest, elasticCpp_justHostNoCredNoMessage) {
  json jResponse;
  std::string sResponse;

  EXPECT_NO_THROW( jResponse = elastic_cpp(TEST_URI, "", json(),
      POST, true, false) );
  EXPECT_NO_THROW( jResponse = elastic_cpp(TEST_URI, "", std::string(),
      POST, true, false) );

  std::cout << jResponse.dump(3) << std::endl;
  std::cout << sResponse << std::endl;
}

TEST(elasticppTest, elasticCpp_Timing) {
  const int verbose = 0;

  const std::string url = "some-index-*/_search?size=0";

  const std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
  for ( int i = 0; i< 10; ++i ) {
    const json jResponse =        elastic_cpp(TEST_URI + url, TEST_CRED, json(),          POST, false, verbose);
    std::cout << "jResponse: " << jResponse.dump(3) << std::endl;
    const std::string sResponse = elastic_cpp(TEST_URI + url, TEST_CRED, std::string(""), POST, false, verbose);
    std::cout << "sResponse: " << json::parse(sResponse).dump(3) << std::endl;
  }
  const std::chrono::time_point<std::chrono::system_clock> stop = std::chrono::system_clock::now();

  const int elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>
                           (stop-start).count();
  std::cout << "elapsed time: " << elapsed_seconds << "ms\n";
}

TEST(elasticppTest, elasticCpp_Aggregation) {
  const int verbose = 0;

  const std::string url = "some-index-*/_search?size=0";
  const json avgIaq = "{ \
\"aggs\": { \
 \"time_ranges\": { \
   \"range\": { \
     \"field\": \"@timestamp\", \
     \"ranges\": [ \
       { \
         \"from\": \"now-10d\", \
         \"to\": \"now\" \
       } \
     ] \
   }, \
   \"aggs\": { \
     \"some_avg\": { \
       \"avg\": { \
         \"field\": \"someField\" \
         } \
       } \
     } \
   } \
  }, \
  \"size\": 0 \
}"_json;

  json response = elastic_cpp(TEST_URI + url, TEST_CRED, avgIaq, POST, verbose);
  std::cout << "response: " << response.dump(3) << std::endl;
}

TEST(elasticppTest, elasticCpp_CreateIndex) {
  const std::string url = "some-index-1";

  const json response = elastic_cpp(TEST_URI + url, TEST_CRED, json(), PUT);

  std::cout << "response: " << response.dump(3) << std::endl;
}

TEST(elasticppTest, elasticCpp_DeleteIndex) {
  const std::string url = "some-index-1";

  const json response = elastic_cpp(TEST_URI + url, TEST_CRED, json(), DELETE);

  std::cout << "response: " << response.dump(3) << std::endl;
}
