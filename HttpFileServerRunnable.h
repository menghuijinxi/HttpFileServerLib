#pragma once

#include "httplib.h"
#include "IHttpFileServer.h"
#include "vector"
#include "string"

class FHttpFileServerRunnable : public IHttpFileServer
{
	//http服务器
	httplib::Server HttpServer;

	std::vector<std::string> FolderPath;

	//查找静态文件
	bool FindStaticFile(const httplib::Request& Request, httplib::Response& Response);

public:
	virtual uint32_t Run(const std::vector<std::string> &inFolderPath, int Port = 8080, const std::string &route = "/") override;
	virtual void Stop() override;
};