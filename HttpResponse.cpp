#include "HttpResponse.h"

HttpResponse::HttpResponse()
{
    m_Response = "HTTP/1.1 200 OK\n"
               "Content-Length: \n"
               "Content-Type: text/html\n"
               "\n"
               "<!DOCTYPE html><html><head><title>Index</title></head><body><h1>Example Index Page</h1></body></html>\n";
}
HttpResponse::~HttpResponse()
{

}

std::string HttpResponse::GetString() const
{
    return m_Response;
}

const char* HttpResponse::GetCString() const
{
    return m_Response.c_str();
}
