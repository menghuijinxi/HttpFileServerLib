#include "HttpFileServerLib.h"
#include "fmt/format.h"

int main()
{
    std::string body;
    FHttpFunction::HttpGet("https://demmenghuijinxi.oss-cn-zhangjiakou.aliyuncs.com/%E5%91%BC%E5%AE%B6%E6%A5%BC%E6%AD%A3%E5%B0%84/meta.json", body);
    fmt::print("body: {}\n", body);

    auto server = FHttpFunction::CreateHttpFileServer();
    server->Run({"test"}, 10003);

    while (true)
    {
        /* code */
    }
    

    return 0;
}