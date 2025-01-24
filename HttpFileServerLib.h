#pragma once
#include <string>
#include <memory>
#include "macro.h"
#include "IHttpFileServer.h"
#include "IHttpResult.h"

class HttpFileServerLib_API FHttpFunction
{
public:
    static std::shared_ptr<IHttpResult> HttpGet(const std::string &uri);

    static std::shared_ptr<IHttpResult> HttpPost(const std::string &uri, const std::string &body, const std::string &content_type);

    static int32_t HttpTest();

    static std::shared_ptr<IHttpFileServer> CreateHttpFileServer();
};
