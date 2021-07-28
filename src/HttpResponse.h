#pragma once

#include <unordered_map>
#include <vector>

namespace Prism
{

class HttpResponse
{
public:

    enum HttpResponseCode {
        OK = 200,
        NOT_FOUND = 404,
        NOT_IMPLEMENTED = 501
    };

    HttpResponse();
    ~HttpResponse();
    inline std::string GetResponseHttpVersion() const { return m_ResponseHttpVersion; }
    inline void SetResponseHttpVersion(const std::string& version) { m_ResponseHttpVersion = version; }
    inline HttpResponseCode GetResponseCode() const { return m_ResponseCode; }
    inline void SetResponseCode(HttpResponseCode code) { m_ResponseCode = code; }
    inline void AddHeader(const std::string& header) { m_ResponseHeaders.push_back(header); }
    inline std::string GetResponseBody() const { return m_ResponseBody; }
    inline void SetResponseBody(const std::string& body) { m_ResponseBody = body; }

    std::string GetString() const;

    static std::string GetStatusText(HttpResponseCode code);

private:
    std::string m_ResponseHttpVersion;
    HttpResponseCode m_ResponseCode;
    std::vector<std::string> m_ResponseHeaders;
    std::string m_ResponseBody;

    static std::unordered_map<HttpResponseCode, std::string> s_StatusTextMap;
};

}