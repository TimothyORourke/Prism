#pragma once
#include "HttpResponse.h"

#include <array>
#include <memory>

namespace Prism
{

class ISocket
{
public:

    enum Type {
        IPV4,
        IPV6
    };

    ISocket() = default;
    virtual ~ISocket() = default;

    virtual bool Bind() = 0;
    virtual bool Listen() = 0;
    virtual std::unique_ptr<ISocket> Accept() = 0;
    virtual int Read(char* buffer, size_t size) = 0;
    virtual int Write(const HttpResponse& response) = 0;
    virtual bool Close() = 0;

    virtual std::string GetIPAddress() const = 0;
    virtual int GetPort() const = 0;
};

}