#pragma once
#include <string>

class IHttpResponse
{
public:
    virtual std::string GetString() const = 0;
    virtual const char* GetCString() const = 0;
};
