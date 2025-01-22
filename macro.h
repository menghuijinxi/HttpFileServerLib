#ifdef _WIN32
#ifdef HttpFileServerLib_EXPORTS
#define HttpFileServerLib_API __declspec(dllexport)
#else
#define HttpFileServerLib_API __declspec(dllimport)
#endif
#else
#define HttpFileServerLib_API
#endif