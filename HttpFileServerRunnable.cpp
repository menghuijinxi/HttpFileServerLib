#include "HttpFileServerRunnable.h"
#include "nlohmann/json.hpp"
#include "boost/algorithm/string.hpp"
#include <boost/filesystem.hpp>
#include <boost/nowide/convert.hpp>

bool FHttpFileServerRunnable::FindStaticFile(const httplib::Request& Request, httplib::Response& Response)
{
	return false;
}

uint32_t FHttpFileServerRunnable::Run(const std::vector<std::string> &inFolderPath, int Port, const std::string &route)
{
	FolderPath = inFolderPath;

	HttpServer.Get("/API/FindFile", [this](const httplib::Request& req, httplib::Response& res)
	{
			std::string findFolderPath;
			for(auto& p : req.params)
			{
				if (boost::algorithm::equals("FindFolder", p.first, boost::algorithm::is_iequal()))
				{
					findFolderPath = p.second;
				}
			}

			nlohmann::json json;
		
			for (auto& path : FolderPath)
			{
				boost::filesystem::path folderPath = findFolderPath.size() <= 0 ? path : boost::filesystem::path(path) / findFolderPath;
				if(!boost::filesystem::exists(folderPath))
				{
					continue;
				}
				for (const auto &iter : boost::filesystem::recursive_directory_iterator(folderPath))
				{
					if (!iter.is_directory())
					{
						#if _WIN32
						std::string p = boost::nowide::narrow(iter.path().lexically_relative(folderPath).wstring());
						json.push_back(p);
						#else
						json.push_back(iter.path().lexically_relative(folderPath).string());
						#endif
					}
				}
			}

			res.set_content(json.dump(), "application/json");
			res.set_header("Access-Control-Allow-Origin", "*");
	});

	for (auto& path : FolderPath)
	{
		HttpServer.set_mount_point(route, path);
	}

	HttpServer.listen("0.0.0.0", Port);

	return true;
}

void FHttpFileServerRunnable::Stop()
{
	HttpServer.stop();
}