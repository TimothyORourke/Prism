#include "HttpResponseBuilder.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace Prism
{

HttpResponseBuilder& HttpResponseBuilder::SetRequestMethod(HttpRequest::Method method)
{
    m_RequestMethod = method;
    return *this;
}

HttpResponseBuilder& HttpResponseBuilder::SetResourcePath(const std::string& path)
{
    m_ResourcePath = path;
    return *this;
}

HttpResponse HttpResponseBuilder::Build()
{
    HttpResponse response;

    if (m_RequestMethod == HttpRequest::GET)
    {
        GenerateHttpGetResponse(response);
    }
    else if (m_RequestMethod == HttpRequest::HEAD)
    {
        GenerateHttpHeadResponse(response);
    }
    else
    {
        response.SetResponseHttpVersion("HTTP/1.1");
        response.SetResponseCode(HttpResponse::NOT_IMPLEMENTED);
        response.SetResponseBody(GetDefault501ResponseBody(HttpRequest::GetMethodText(m_RequestMethod)));
    }

    return response;
}

void HttpResponseBuilder::GenerateHttpGetResponse(HttpResponse& response)
{
    if (m_ResourcePath == "/")
    {
        m_ResourcePath = "/index.html";
    }

    std::ifstream resource(m_ResourcePath.substr(1, m_ResourcePath.length() - 1));
    if (resource) // Resource exists.
    {
        std::stringstream ss;
        while (resource.good())
        {
            resource >> ss.rdbuf();
        }

        response.SetResponseHttpVersion("HTTP/1.1");
        response.SetResponseCode(HttpResponse::OK);
        response.SetResponseBody(ss.str());
        response.AddHeader("Content-Length", std::to_string(ss.str().size()));
    }
    else
    {
        // Create 404 response.
        response.SetResponseHttpVersion("HTTP/1.1");
        response.SetResponseCode(HttpResponse::NOT_FOUND);
        response.SetResponseBody(GetDefault404ResponseBody(m_ResourcePath));
    }
}

void HttpResponseBuilder::GenerateHttpHeadResponse(HttpResponse& response)
{
    if (m_ResourcePath == "/")
    {
        m_ResourcePath = "/index.html";
    }

    std::ifstream resource(m_ResourcePath.substr(1, m_ResourcePath.length() - 1));
    if (resource) // Resource exists.
    {
        std::stringstream ss;
        while (resource.good())
        {
            resource >> ss.rdbuf();
        }

        response.SetResponseHttpVersion("HTTP/1.1");
        response.SetResponseCode(HttpResponse::OK);
    }
    else
    {
        // Create 404 response.
        response.SetResponseHttpVersion("HTTP/1.1");
        response.SetResponseCode(HttpResponse::NOT_FOUND);
    }
}

std::string HttpResponseBuilder::GetDefault404ResponseBody(const std::string& resourcePath) const
{
    return  "<!DOCTYPE html><html><head><title>404 - Not Found</title></head><body>"
            "<h1>Not Found</h1>"
            "<p>The requested URL " + resourcePath + " was not found on this server.</p>"
            "<hr>"
            "</body></html>\n";
}

std::string HttpResponseBuilder::GetDefault501ResponseBody(const std::string& method) const
{
    return  "<!DOCTYPE html><html><head><title>501 - Not Implemented</title></head><body>"
            "<h1>Not Implemented</h1>"
            "<p>The HTTP request method " + method + " is not implemented by this server.</p>"
            "<hr>"
            "</body></html>\n";
}

}