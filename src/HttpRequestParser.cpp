#include "HttpRequestParser.h"

#include <sstream>

namespace Prism
{

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
    else if (method == "POST")
    {
        newRequest.SetMethod(HttpRequest::POST);
    }
    else if (method == "PUT")
    {
        newRequest.SetMethod(HttpRequest::PUT);
    }
    else if (method == "DELETE")
    {
        newRequest.SetMethod(HttpRequest::DELETE);
    }
    else
    {
        newRequest.SetMethod(HttpRequest::INVALID);
    }

    newRequest.SetPath(path);
    newRequest.SetVersion(version);

    return newRequest;
}

}