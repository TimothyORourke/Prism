#pragma once

#include "HttpHeader.h"

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

    HttpResponse() {}
    ~HttpResponse() {}

    inline std::string GetResponseHttpVersion() const { return m_HttpVersion; }
    inline HttpResponseCode GetResponseCode() const { return m_ResponseCode; }
    inline std::vector<HttpHeader> GetHeaders() const { return m_Headers; }
    inline std::string GetResponseBody() const { return m_Body; }
    inline void SetResponseHttpVersion(const std::string& version) { m_HttpVersion = version; }
    inline void SetResponseCode(HttpResponseCode code) { m_ResponseCode = code; }
    inline void AddHeader(const std::string& name, const std::string& value) { m_Headers.push_back({name, value}); }
    inline void SetResponseBody(const std::string& body) { m_Body = body; }

    static std::string GetStatusText(HttpResponseCode code) { return s_StatusTextMap[code]; }

    std::string GetHeadersString() const;
    std::string ToString() const;

private:
    std::string m_HttpVersion;
    HttpResponseCode m_ResponseCode;
    std::vector<HttpHeader> m_Headers;
    std::string m_Body;

    static std::unordered_map<HttpResponseCode, std::string> s_StatusTextMap;
};

}