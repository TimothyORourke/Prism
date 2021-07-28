#include "HttpRequest.h"
#include "HttpResponse.h"

#include <string>
#include <vector>

namespace Prism
{

class HttpResponseBuilder
{
public:
    HttpResponseBuilder();
    ~HttpResponseBuilder();

    HttpResponseBuilder& SetRequestMethod(HttpRequest::Method method);
    HttpResponseBuilder& SetResourcePath(const std::string& path);
    HttpResponseBuilder& SetRequestHeaders(const std::vector<std::string> headers);
    HttpResponse Build();

private:
    void GenerateHttpGETResponse(HttpResponse& response);
    void GenerateHttpHEADResponse(HttpResponse& response);
    std::string GetDefault404ResponseBody(const std::string& resourcePath) const;

private:
    HttpRequest::Method m_RequestMethod;
    std::string m_ResourcePath;
    std::vector<std::string> m_RequestHeaders;
};

}