#include "HttpRequest.h"

namespace Prism
{

std::unordered_map<HttpRequest::Method, std::string> HttpRequest::s_MethodTextMap = 
    {
        {HttpRequest::Method::GET, "GET"},
        {HttpRequest::Method::HEAD, "HEAD"},
        {HttpRequest::Method::POST, "POST"},
        {HttpRequest::Method::PUT, "PUT"},
        {HttpRequest::Method::DELETE, "DELETE"},
    };

}
