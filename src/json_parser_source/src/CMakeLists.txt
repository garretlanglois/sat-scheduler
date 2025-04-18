cmake_minimum_required(VERSION 3.5)
project(CommandParser LANGUAGES CXX)

include_directories("../include/rapidjson")

add_definitions(-DCOMMAND_PARSER_EXPORTS)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC -m64 -O2")

add_library(command_parser SHARED command_parser.cpp)

add_library(command_parser_obj OBJECT command_parser.cpp)


set_target_properties(
  command_parser
  PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)


message(STATUS "After building, the object file(s) for command_parser_obj will be "
  "$<TARGET_OBJECTS:command_parser_obj>"
)

install(TARGETS command_parser
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
install(FILES command_parser.h DESTINATION include)
