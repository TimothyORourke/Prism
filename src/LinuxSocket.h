#pragma once

#include "ISocket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

namespace Prism
{

class LinuxSocket : public ISocket
{
public:
    LinuxSocket(ISocket::Type type, const std::string& ipAddress, int port);
    LinuxSocket(int socketID, ISocket::Type type, const std::string& ipAddress, int port);
    ~LinuxSocket();
    virtual bool Bind() override;
    virtual bool Listen() override;
    virtual std::unique_ptr<ISocket> Accept() override;
    virtual int Read(char* buffer, size_t size) override;
    virtual int Write(const HttpResponse& response) override;
    virtual bool Close() override;

    virtual std::string GetIPAddress() const override;
    virtual int GetPort() const override;

private:
    int m_SocketID;
    std::string m_IPAddress;
    int m_Port;
    ISocket::Type m_Type;
};

}