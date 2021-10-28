#include "HttpRequest.h"
#include "HttpResponse.h"

#include <string>
#include <vector>

namespace Prism
{

class HttpResponseBuilder
{
public:
    HttpResponseBuilder() {}
    ~HttpResponseBuilder() {}

    HttpResponseBuilder& SetRequestMethod(HttpRequest::Method method);
    HttpResponseBuilder& SetResourcePath(const std::string& path);

    HttpResponse Build();

private:
    void GenerateHttpGetResponse(HttpResponse& response);
    void GenerateHttpHeadResponse(HttpResponse& response);
    std::string GetDefault404ResponseBody(const std::string& resourcePath) const;
    std::string GetDefault501ResponseBody(const std::string& method) const;

private:
    HttpRequest::Method m_RequestMethod;
    std::string m_ResourcePath;
};

}