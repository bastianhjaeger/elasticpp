cmake_minimum_required (VERSION 3.10.2)
project (elasticpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -g")


execute_process (
  COMMAND 
    /bin/bash -c "printf $(git describe --tags)$(git diff --quiet || echo '-dirty')"
  OUTPUT_VARIABLE 
    git_version)
if(NOT DEFINED ${git_version})
  set(git_version "v0.0.0")
endif(NOT DEFINED ${git_version})
string(FIND ${git_version} "-" end_of_version)
if(${end_of_version} LESS 1)
  string(SUBSTRING ${git_version} 1 -1 ELASTICPP_VERSION_SHORT)
else()
  MATH(EXPR end_of_version "${end_of_version}-1")
  string(SUBSTRING ${git_version} 1 ${end_of_version} ELASTICPP_VERSION_SHORT)
endif(${end_of_version} LESS 1)


string(REPLACE "." ";" VERSION_LIST ${ELASTICPP_VERSION_SHORT})
list(GET VERSION_LIST 0 ELASTICPP_VERSION_MAJOR)
list(GET VERSION_LIST 1 ELASTICPP_VERSION_MINOR)
list(GET VERSION_LIST 2 ELASTICPP_VERSION_PATCH)
set(ELASTICPP_VERSION ${git_version})

add_definitions(-D${PROJECT_NAME}_VERSION=\"${git_version}\")
add_definitions(-D${PROJECT_NAME}_VERSION_MAJOR=\"${ELASTICPP_VERSION_MAJOR}\")
add_definitions(-D${PROJECT_NAME}_VERSION_MINOR=\"${ELASTICPP_VERSION_MINOR}\")
add_definitions(-D${PROJECT_NAME}_VERSION_PATCH=\"${ELASTICPP_VERSION_PATCH}\")


set(main_lib_dest "lib")
set(include_dest "include/${PROJECT_NAME}")
set(lib_dest "${main_lib_dest}")
set(tool_dest "bin")

add_subdirectory(src)
add_subdirectory(test)
