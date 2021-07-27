#pragma once
#include "IHttpResponse.h"

#include <unordered_map>

class HttpResponse : public IHttpResponse
{
public:

    enum HttpResponseCode {
        OK = 200,
    };

    HttpResponse(const std::string& response);
    ~HttpResponse();
    virtual std::string GetString() const override;
    virtual const char* GetCString() const override;

    std::string GetStatusText(HttpResponseCode code) const;

private:
    std::string m_Response;
    static std::unordered_map<HttpResponseCode, std::string> s_StatusTextMap;
};