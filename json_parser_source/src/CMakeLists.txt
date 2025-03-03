cmake_minimum_required(VERSION 3.5)
project(CommandParser LANGUAGES CXX)

include_directories("../include/rapidjson")

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags: Add -Wall and -O2. The -fPIC flag is needed for shared libraries.
# If your compiler does not support 64-bit mode with -m64, remove it.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC -m64 -O2")

# Optionally, you can instruct the linker to generate a shared library.
# On Windows, this builds a DLL; on Linux/macOS it builds a .so or .dylib.
add_library(command_parser SHARED command_parser.cpp)

# Also build an object library target so that an object file is generated.
# The object files built by this target are not linked into a final library,
# but you can use them as needed.
add_library(command_parser_obj OBJECT command_parser.cpp)

# Optionally, set the output directories for your artifacts.
set_target_properties(
  command_parser
  PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# Display a message to locate the generated object file.
message(STATUS "After building, the object file(s) for command_parser_obj will be "
  "$<TARGET_OBJECTS:command_parser_obj>"
)

# If you want to install the DLL and header for use with Python, you could add:
install(TARGETS command_parser
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
install(FILES command_parser.h DESTINATION include)
