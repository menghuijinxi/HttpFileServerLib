#include "httplib.h"
#include <boost/filesystem.hpp>
#include <boost/nowide/convert.hpp>

namespace httplib
{

std::shared_ptr<std::ifstream> createFileStream(const std::string &path)
{
    auto wP = boost::nowide::widen(path);
    return std::make_shared<std::ifstream>(wP, std::ios::binary);
}

}