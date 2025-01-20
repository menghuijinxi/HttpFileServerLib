﻿#include "HttpFileServerLib.h"
#include "httplib.h"

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

httplib::Result ClientGetRequest(const std::string &uri)
{
    std::string host, localPath;
    parse_uri_to_Host_LocalPath(uri, host, localPath);
    httplib::Client client(host);
    return client.Get(localPath);
}

httplib::Result ClientPostRequest(const std::string &uri, const std::string &body, const std::string &content_type)
{
    std::string host, localPath;
    parse_uri_to_Host_LocalPath(uri, host, localPath);
    httplib::Client client(host);
    return client.Post(localPath, body, content_type);
}

int32_t FHttpFunction::HttpGet(const std::string &uri, std::string &body)
{
    auto client = ClientGetRequest(uri);
    if (client.error() == httplib::Error::Success && client->status == 200 && client->body.size() > 0)
    {
        body = std::move(client->body);
    }

    return (int32_t)client.error();
}

int32_t FHttpFunction::HttpPost(const std::string &uri, const std::string &body, const std::string &content_type, std::string &response)
{
    auto client = ClientPostRequest(uri, body, content_type);
    if (client.error() == httplib::Error::Success && client->status == 200 && client->body.size() > 0)
    {
        response = std::move(client->body);
    }

    return (int32_t)client.error();
}
