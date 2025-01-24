#pragma once
#include <cstdint>
#include "macro.h"

class HttpFileServerLib_API IHttpResult
{
public:
    virtual const char* GetBody() const = 0;
    virtual size_t GetBodySize() const = 0;
    virtual bool IsSuccess() const = 0;
    virtual ~IHttpResult() = default;
};