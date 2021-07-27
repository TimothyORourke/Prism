#pragma once
#include <string>

class IHttpResponse
{
public:
    virtual std::string GetString() const = 0;
};
