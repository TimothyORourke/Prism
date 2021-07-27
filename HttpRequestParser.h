#pragma once

#include "HttpRequest.h"

#include <string>

namespace Prism
{

class HttpRequestParser
{
public: 
    HttpRequestParser(std::string rawRequest);
    ~HttpRequestParser();

    HttpRequest GetRequest() const;

private:
    std::string m_RawRequest;
};

}
