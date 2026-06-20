# CMakeList.txt : CMake project for ExampleMod, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_library (ExampleMod SHARED "ExampleMod.cpp" "ExampleMod.h")



set(BLOOM_API_DIR "${CMAKE_SOURCE_DIR}/BloomAPI")

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCHITECTURE "x64")
else()
    set(ARCHITECTURE "x86")
endif()

set(BLOOM_LIB "${BLOOM_API_DIR}/bin/${CMAKE_BUILD_TYPE}${ARCHITECTURE}/LawnProject.lib")

target_link_libraries(ExampleMod BLOOM_LIB)

set(BLOOM_INCLUDE "${BLOOM_API_DIR}/include/")

include_directories("${BLOOM_INCLUDE}/Bloom/")
include_directories("${BLOOM_INCLUDE}/Lawn/")
include_directories("${BLOOM_INCLUDE}/SexyAppFramework/")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ExampleMod PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
