cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DCPPHTTPLIB_OPENSSL_SUPPORT=1)
add_definitions(-DHttpFileServerLib_EXPORTS)

project("HttpFileServerLib")

add_library(HttpFileServerLib SHARED "HttpFileServerLib.cpp")
add_executable(HttpTest "main.cpp")

find_package(OpenSSL REQUIRED)
target_link_libraries(HttpFileServerLib PUBLIC OpenSSL::SSL)
target_link_libraries(HttpFileServerLib PUBLIC OpenSSL::Crypto)

find_package(boost_filesystem REQUIRED CONFIG)
target_link_libraries(HttpFileServerLib PRIVATE Boost::filesystem)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(HttpTest PRIVATE fmt::fmt)
target_link_libraries(HttpTest PRIVATE HttpFileServerLib)