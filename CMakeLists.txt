cmake_minimum_required (VERSION 3.8)
project ("tinycheck")

cmake_policy(SET CMP0079 NEW)

if(DEBUG_ENABLE_ADDRESS_SANITIZER)
    set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address,undefined")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address,undefined")
    set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address,undefined")
    message("Building with enabled address sanitizer")
endif()

include_directories(include)
add_executable (tinycheck "logging.cpp" "main.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET tinycheck PROPERTY CXX_STANDARD 20)
endif()

enable_testing()
