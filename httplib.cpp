#include "httplib.h"
#include <boost/filesystem.hpp>
#include <boost/nowide/convert.hpp>

namespace httplib
{
    std::shared_ptr<std::ifstream> createFileStream(const std::string &path, const std::string &basePath)
    {
        auto s = basePath + path;
        #if _WIN32
            auto wP = boost::nowide::widen(s);
            return std::make_shared<std::ifstream>(wP, std::ios::binary);
        #else
            return std::make_shared<std::ifstream>(s, std::ios::binary);
        #endif
    }

}