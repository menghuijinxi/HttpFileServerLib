#pragma once
#include <string>
#include <memory>
#include "macro.h"
#include "IHttpFileServer.h"

class HttpFileServerLib_API FHttpFunction
{
public:
    static int32_t HttpGet(const std::string &uri, std::string &body);

    static int32_t HttpPost(const std::string &uri, const std::string &body, const std::string &content_type, std::string &response);

    static int32_t HttpTest();

    static std::shared_ptr<IHttpFileServer> CreateHttpFileServer();
};
