#include <elasticpp/ElastiCpp.h>

#include <thread>
#include <chrono>

#include <gtest/gtest.h>

using namespace elasticpp;

const std::string TEST_URI = "http://localhost:9200/";
const std::string TEST_CRED = "user:password";

class ElastiCppTest : public ::testing::Test{
public:
  ElastiCppTest() :
      ec(ElastiCpp(TEST_URI, TEST_CRED)) { };

private:
  ElastiCpp ec;
};

TEST_F(ElastiCppTest, createIndex) {
  ElastiCpp ec(TEST_URI, TEST_CRED);
  const int verbose = 1;

  const std::string url = "test_index";
  const bool success = ec.createIndex(url, 1, 1, verbose);

  EXPECT_TRUE(success);
}

TEST_F(ElastiCppTest, getIndex) {
  ElastiCpp ec(TEST_URI, TEST_CRED);
  const int verbose = 1;

  const std::string url = "test_index";
  const json response = ec.getIndex(url, verbose);

  std::cout << "response: " << response.dump(3) << std::endl;

  EXPECT_FALSE(response.empty());
}


TEST_F(ElastiCppTest, query) {
  ElastiCpp ec(TEST_URI, TEST_CRED);
  const int verbose = 1;

  const json GET_IAQ_STATS_FOR_TIME_PROJ_AND_DEVICE =
      json::parse("{ \"size\": 0, \"aggs\": { \"time_ranges\": { \"range\": { \"field\": \"@timestamp\", \"ranges\": [ { \"from\": \"now-1d\", \"to\": \"now\" } ] }, \"aggs\": { \"term_cust\": { \"terms\": { \"field\": \"customer.keyword\" }, \"aggs\": { \"term_dev\": { \"terms\": { \"field\": \"name.keyword\" }, \"aggs\": { \"term_hex\": { \"terms\": { \"field\": \"id_hex.keyword\" }, \"aggs\": { \"iaq_stat\": { \"stats\": { \"field\": \"iaq\" } }, \"ir_max\": { \"max\": { \"field\": \"ir\" } }, \"time_stat\": { \"stats\": { \"field\": \"@timestamp\" } } } } } } } } } } } }");


  const std::string url = "live-2020*/_search";
  const json response = ec.send(url, GET_IAQ_STATS_FOR_TIME_PROJ_AND_DEVICE);

  const json response2 = ec.send("index_*/_search", R"({"query": {"match_all": {}}})");

  std::cout << "response: " << response.dump(3) << std::endl;

//  json byTime = response["aggregations"];
//  for ( const auto& timeBucket : byTime["time_ranges"]["buckets"] ) {
//    for ( const auto& custBucket : timeBucket["term_cust"]["buckets"] ) {
//      for ( const auto& deviceBucket : custBucket["term_dev"]["buckets"] ) {
//        for ( const auto& hexBucket : deviceBucket["term_hex"]["buckets"] ) {
//          std::cout << timeBucket["key"] << " ";
//          std::cout << custBucket["key"] << " ";
//          std::cout << deviceBucket["key"] << " ";
//          std::cout << hexBucket["key"] << " " << std::endl;
//          std::cout << hexBucket["iaq_stat"].dump(3)  << std::endl;
//        }
//      }
//    }
//  }
}


TEST_F(ElastiCppTest, deleteIndex) {
  ElastiCpp ec(TEST_URI, TEST_CRED);
  const int verbose = 1;

  const std::string url = "test_index";
  const bool success = ec.deleteIndex(url, verbose);

  EXPECT_TRUE(success);
}
