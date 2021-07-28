#pragma once

#include "HttpRequest.h"
#include "ISocket.h"

namespace Prism
{

class Server
{
public:
    Server();
    ~Server();
    void Run() const;
    bool Shutdown();

private:
    void ServerSocketSetup() const;
    HttpRequest GetClientHttpRequest(const std::unique_ptr<ISocket>& clientSocket) const;
    void HandleRequest(const HttpRequest& request, const std::unique_ptr<ISocket>& clientSocket) const;

private:
    std::unique_ptr<ISocket> m_ServerSocket;
};

}