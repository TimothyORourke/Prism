#include "HttpRequestParser.h"

#include <sstream>

namespace Prism
{

HttpRequestParser::HttpRequestParser(std::string rawRequest)
    : m_RawRequest(rawRequest)
{

}

HttpRequestParser::~HttpRequestParser()
{

}

HttpRequest HttpRequestParser::GetRequest() const
{
    HttpRequest newRequest;

    std::string method, path, version;
    std::stringstream ss(m_RawRequest);
    ss >> method >> path >> version;

    if (method == "GET")
    {
        newRequest.SetMethod(HttpRequest::GET);
    }
    else if (method == "HEAD")
    {
        newRequest.SetMethod(HttpRequest::HEAD);
    }

    newRequest.SetPath(path);
    newRequest.SetVersion(version);

    return newRequest;
}

}