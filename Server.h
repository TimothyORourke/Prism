#pragma once

#include "ISocket.h"

class Server
{
public:
    Server();
    ~Server();
    void Run() const;
    bool Shutdown();

private:
    std::unique_ptr<ISocket> m_ServerSocket;
};