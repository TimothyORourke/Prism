#pragma once

#include "HttpRequest.h"

#include <string>

namespace Prism
{

class HttpRequestParser
{
public: 
    HttpRequestParser(const std::string& rawRequest) : m_RawRequest(rawRequest) {}
    ~HttpRequestParser() {}

    HttpRequest GetRequest() const;

private:
    std::string m_RawRequest;
};

}
