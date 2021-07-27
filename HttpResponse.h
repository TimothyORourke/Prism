#pragma once
#include "IHttpResponse.h"

class HttpResponse : public IHttpResponse
{
public:
    HttpResponse();
    ~HttpResponse();
    virtual std::string GetString() const override;
    virtual const char* GetCString() const override;

private:
    std::string m_Response;
};