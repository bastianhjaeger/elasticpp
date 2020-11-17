#pragma once

#include <stdio.h>
#include <sstream>


#if __GNUC__ > 7
  #include <filesystem>
  namespace fs = std::filesystem;
#else
  #include <experimental/filesystem>
  namespace fs = std::experimental::filesystem;
#endif


#define ERR_STRING  "\033[1;31m[ERROR]\033[0m"
#define DBG_STRING  "\033[1;32m[DEBUG]\033[0m"
#define INFO_STRING "\033[1;34m[INFO] \033[0m"

#if 1
#define error(msg) \
  std::cerr << ERR_STRING; \
  std::cerr << " " << msg << std::endl;
#else
#define error(msg)
#endif

#if 0
#define debug(msg) \
  std::cout << DBG_STRING; \
  std::cout << " " << msg << std::endl;
#else
#define debug(msg)
#endif

#if 1
#define info(msg) \
  std::cout << INFO_STRING; \
  std::cout << " " << msg << std::endl;
#else
#define info(msg)
#endif
