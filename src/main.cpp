#include <elasticpp/version.h>

#include <iostream>

int main(int argc, char** argv) {
  std::cout << elasticpp_VERSION << std::endl;

  std::cout << "  major: " << elasticpp_VERSION_MAJOR << std::endl;
  std::cout << "  minor: " << elasticpp_VERSION_MINOR << std::endl;
  std::cout << "  patch: " << elasticpp_VERSION_PATCH << std::endl;

  return 0;
}
