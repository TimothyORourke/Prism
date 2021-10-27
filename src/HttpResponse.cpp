#include "HttpResponse.h"

namespace Prism
{

std::unordered_map<HttpResponse::HttpResponseCode, std::string> HttpResponse::s_StatusTextMap = 
    {
        {HttpResponse::HttpResponseCode::OK, "OK"},
        {HttpResponse::HttpResponseCode::NOT_FOUND, "Not Found"},
        {HttpResponse::HttpResponseCode::NOT_IMPLEMENTED, "Not Implemented"}
    };

HttpResponse::HttpResponse()
{
}

HttpResponse::~HttpResponse()
{

}

std::string HttpResponse::GetString() const
{
    std::string responseString;

    responseString += m_ResponseHttpVersion + " " + std::to_string(m_ResponseCode) 
                   + " " + GetStatusText(m_ResponseCode) + "\n";

    responseString += GetHeadersString();

    responseString += "\n" + m_ResponseBody;

    return responseString;
}

std::string HttpResponse::GetHeadersString() const
{
    std::string responseHeadersString;

    for (const auto& header : m_ResponseHeaders)
    {
        responseHeadersString += header + "\n";
    }

    return responseHeadersString;
}

std::string HttpResponse::GetStatusText(HttpResponseCode code)
{
    return s_StatusTextMap[code];
}

}