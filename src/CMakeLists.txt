set(header_path "${${PROJECT_NAME}_SOURCE_DIR}/include/${PROJECT_NAME}")
set(header ${header_path}/${PROJECT_NAME}.h
		   ${header_path}/ElastiCpp.h
		   ${header_path}/json.hpp)

set(src ${PROJECT_NAME}.cpp
        ElastiCpp.cpp)


configure_file("version.h.in" "${CMAKE_CURRENT_BINARY_DIR}/version.h")


add_library(${PROJECT_NAME} SHARED
  ${header}
  ${src})
target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
         ${elasticpp_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}
  stdc++fs
  pthread
  curl)
  
add_library(${PROJECT_NAME}_static STATIC
  ${header}
  ${src})
target_include_directories(${PROJECT_NAME}_static
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
         ${elasticpp_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}_static
  stdc++fs
  pthread
  curl)
  
add_executable(${PROJECT_NAME}.info main.cpp)
target_include_directories(${PROJECT_NAME}.info
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
         ${elasticpp_SOURCE_DIR}/include)


install(TARGETS ${PROJECT_NAME}
		LIBRARY DESTINATION "${main_lib_dest}"
        ARCHIVE DESTINATION "${main_lib_dest}"
        COMPONENT library)
install(TARGETS ${PROJECT_NAME}.info
		RUNTIME DESTINATION "${tool_dest}"
        COMPONENT library)
install(FILES ${header} DESTINATION "${include_dest}")
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/version.h
        DESTINATION "${include_dest}")
