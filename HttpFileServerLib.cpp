#include "HttpFileServerLib.h"
#include "httplib.h"
#include "HttpFileServerRunnable.h"
#include "IHttpResult.h"

void parse_uri_to_Host_LocalPath(const std::string &uri,
                                 std::string &host, std::string &localPath)
{
    const static std::regex re(
        R"(^(?:(https?):)?(?://([^:/?#]*)(?::(\d+))?)?([^?#]*(?:\?[^#]*)?)(?:#.*)?)");

    std::smatch m;
    if (!std::regex_match(uri, m, re))
    {
        return;
    }
    localPath = m[4].str();
    host = uri.substr(0, uri.size() - localPath.size());
}

class FHttpLibResult : public IHttpResult
{
public:

    httplib::Result Result;

    virtual bool IsSuccess() const override
    {
        return Result.error() == httplib::Error::Success && Result->status == 200 && Result->body.size() > 0;
    }

    virtual const char* GetBody() const override
    {
        return Result->body.c_str();
    }

    virtual size_t GetBodySize() const override
    {
        return Result->body.size();
    }
};

std::shared_ptr<FHttpLibResult> ClientGetRequest(const std::string &uri)
{
    std::shared_ptr<FHttpLibResult> result = std::make_shared<FHttpLibResult>();
    std::string host, localPath;
    parse_uri_to_Host_LocalPath(uri, host, localPath);
    httplib::Client client(host);
    result->Result = client.Get(localPath);
    return result;
}

std::shared_ptr<FHttpLibResult> ClientPostRequest(const std::string &uri, const std::string &body, const std::string &content_type)
{
    std::string host, localPath;
    parse_uri_to_Host_LocalPath(uri, host, localPath);
    httplib::Client client(host);
    std::shared_ptr<FHttpLibResult> result = std::make_shared<FHttpLibResult>();
    result->Result = client.Post(localPath, body, content_type);
    return result;
}

std::shared_ptr<IHttpResult> FHttpFunction::HttpGet(const std::string &uri)
{
    return ClientGetRequest(uri);
}

std::shared_ptr<IHttpResult> FHttpFunction::HttpPost(const std::string &uri, const std::string &body, const std::string &content_type)
{
    return ClientPostRequest(uri, body, content_type);
}

int32_t FHttpFunction::HttpTest()
{
    auto reulst = HttpGet("https://demmenghuijinxi.oss-cn-zhangjiakou.aliyuncs.com/%E5%91%BC%E5%AE%B6%E6%A5%BC%E6%AD%A3%E5%B0%84/meta.json");
    return reulst->IsSuccess();
}

std::shared_ptr<IHttpFileServer> FHttpFunction::CreateHttpFileServer()
{
    return std::make_shared<FHttpFileServerRunnable>();
}