# General
![ElastiCpp-Release](https://github.com/bastianhjaeger/elasticpp/workflows/ElastiCpp-Release/badge.svg?branch=master)
![ElastiCpp-Debug](https://github.com/bastianhjaeger/elasticpp/workflows/ElastiCpp-Debug/badge.svg?branch=master)

Interface to manipulate elasticsearch by REST API from c++. 

# Installation
```bash
git clone git@github.com:bastianhjaeger/elasticpp.git
cd elasticpp
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j8
sudo make install
```

# Usage

## plain functions
```c++
#include <elasticpp/elasticpp.h>

const bool singleCall = true;
const bool verbose = true;

const std::string sResponse 
    = elastic_cpp("http://localhost:9200/test", "", "", PUT, singleCall, verbose);
const json jResponse 
    = elastic_cpp("http://localhost:9200/test", "", json(), PUT);
```

## class implementation
```c++
#include <elasticpp/ElastiCpp.h>

const int verbose = 0;
const int shards = 1;
const int replicas = 1;
const std::string url = "test_index";

ElastiCpp ec("http://localhost:9200/", "user:password");

bool success = ec.createIndex(url, shards, replicas, verbose);

const json response = ec.getIndex(url, verbose);
std::cout << "response: " << response.dump(3) << std::endl;

success = ec.deleteIndex(url, verbose);

// or any randon message/query
const json response2 = ec.send("index_*/_search", R"({"query": {"match_all": {}}})");
```
# Othres
Thanks to   JSON for Modern C++ (version 3.7.2)  https://github.com/nlohmann/json
