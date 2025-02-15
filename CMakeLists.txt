cmake_minimum_required (VERSION 3.8)

# 必须在add_library ， add_executable 前设置，否则无效。让脚本的字符串使用utf8格式编译
#add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/execution-charset:utf-8>") 

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DCPPHTTPLIB_OPENSSL_SUPPORT=1)
add_definitions(-DHttpFileServerLib_EXPORTS)

project("HttpFileServerLib")

add_library(HttpFileServerLib SHARED "HttpFileServerLib.cpp" "HttpFileServerRunnable.cpp" "httplib.cpp")
add_executable(HttpTest "main.cpp")

find_package(OpenSSL REQUIRED)
target_link_libraries(HttpFileServerLib PUBLIC OpenSSL::SSL)
target_link_libraries(HttpFileServerLib PUBLIC OpenSSL::Crypto)

find_package(boost_filesystem REQUIRED CONFIG)
target_link_libraries(HttpFileServerLib PRIVATE Boost::filesystem)

find_package(boost_nowide REQUIRED CONFIG)
target_link_libraries(HttpFileServerLib PRIVATE Boost::nowide)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(HttpTest PRIVATE fmt::fmt)
target_link_libraries(HttpTest PRIVATE HttpFileServerLib)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(HttpFileServerLib PRIVATE nlohmann_json nlohmann_json::nlohmann_json)

find_package(boost_algorithm REQUIRED CONFIG)
target_link_libraries(HttpFileServerLib PRIVATE Boost::algorithm)

install(TARGETS HttpFileServerLib)
install(FILES HttpFileServerLib.h macro.h IHttpFileServer.h IHttpResult.h DESTINATION include)