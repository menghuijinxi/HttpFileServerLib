#include "HttpFileServerLib.h"
#include "fmt/format.h"

int main()
{
    auto reulst = FHttpFunction::HttpGet("https://demmenghuijinxi.oss-cn-zhangjiakou.aliyuncs.com/%E5%91%BC%E5%AE%B6%E6%A5%BC%E6%AD%A3%E5%B0%84/meta.json");
    fmt::print("body: {}\n", reulst->GetBody());

    auto server = FHttpFunction::CreateHttpFileServer();
    server->Run({"test", "测试1"}, 10003);

    while (true)
    {
        /* code */
    }
    

    return 0;
}