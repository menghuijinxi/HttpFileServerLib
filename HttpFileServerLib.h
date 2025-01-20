#include <string>

#ifdef HttpFileServerLib_EXPORTS
#define HttpFileServerLib_API __declspec(dllexport)
#else
#define HttpFileServerLib_API __declspec(dllimport)
#endif

class HttpFileServerLib_API HttpFileServerLib
{

};

class HttpFileServerLib_API FHttpFunction
{
public:
    static int32_t HttpGet(const std::string &uri, std::string &body);

    static int32_t HttpPost(const std::string &uri, const std::string &body, const std::string &content_type, std::string &response);
};
