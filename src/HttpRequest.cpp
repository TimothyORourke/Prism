#include "HttpRequest.h"

namespace Prism
{

std::unordered_map<HttpRequest::Method, std::string> HttpRequest::s_MethodTextMap = 
    {
        {HttpRequest::Method::GET, "GET"},
        {HttpRequest::Method::HEAD, "HEAD"}
    };

HttpRequest::HttpRequest()
{

}

HttpRequest::~HttpRequest()
{

}

HttpRequest::Method HttpRequest::GetMethod() const
{
    return m_Method;
}

void HttpRequest::SetMethod(HttpRequest::Method method)
{
    m_Method = method;
}

std::string HttpRequest::GetPath() const
{
    return m_Path;
}

void HttpRequest::SetPath(const std::string& path)
{
    m_Path = path;
}

std::string HttpRequest::GetMethodText() const
{
    return s_MethodTextMap[m_Method];
}

std::string HttpRequest::GetVersion() const
{
    return m_Version;
}

void HttpRequest::SetVersion(const std::string& version)
{
    m_Version = version;
}

}