#pragma once
#include <cstdint>
#include "macro.h"
#include "vector"

class HttpFileServerLib_API IHttpFileServer 
{
public:
    virtual uint32_t Run(const std::vector<std::string> &inFolderPath, int Port = 8080, const std::string &route = "/") = 0;
    virtual void Stop() = 0;
    virtual ~IHttpFileServer() = default;
};