#include "HttpResponse.h"

namespace Prism
{

std::unordered_map<HttpResponse::HttpResponseCode, std::string> HttpResponse::s_StatusTextMap = 
    {
        {HttpResponse::HttpResponseCode::OK, "OK"},
        {HttpResponse::HttpResponseCode::NOT_FOUND, "Not Found"},
        {HttpResponse::HttpResponseCode::NOT_IMPLEMENTED, "Not Implemented"},
    };

std::string HttpResponse::GetHeadersString() const
{
    std::string responseHeadersString;

    for (const auto& header : m_Headers)
    {
        responseHeadersString += header.ToString() + "\n";
    }

    return responseHeadersString;
}

std::string HttpResponse::ToString() const
{
    std::string responseString;

    responseString += m_HttpVersion + " " + std::to_string(m_ResponseCode) 
                   + " " + GetStatusText(m_ResponseCode) + "\n";

    responseString += GetHeadersString();

    responseString += "\n" + m_Body;

    return responseString;
}

}