#include "Server.h"

#include "HttpResponse.h"
#include "LinuxSocket.h"

#include <cstring>
#include <iostream>
#include <sstream>

Server::Server()
{
    m_ServerSocket = std::make_unique<LinuxSocket>(ISocket::Type::IPV4, "", 8000);
}

Server::~Server()
{
    Shutdown();
}

void Server::Run() const
{
    if (!m_ServerSocket->Bind())
    {
        std::cout << "Error: server socket failed to bind." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!m_ServerSocket->Listen())
    {
        std::cout << "Error: server socket failed to listen." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    while (true)
    {
        auto clientSocket = m_ServerSocket->Accept();

        char requestBuffer[10000];
        memset(&requestBuffer, 0, sizeof(requestBuffer));
        int read = clientSocket->Read(requestBuffer, 10000);
        std::stringstream ss(requestBuffer);
        char requestFirstLine[100];
        memset(&requestFirstLine, 0, sizeof(requestFirstLine));
        ss.getline(requestFirstLine, 100);
        
        //std::cout << requestBuffer << std::endl;

        std::cout << clientSocket->GetIPAddress() << ":" << clientSocket->GetPort() << "\n" << requestFirstLine << std::endl;
        std::cout << "bytes read: " << read << std::endl;
        //std::cout << requestBuffer;

        HttpResponse response;
        clientSocket->Write(response);
        clientSocket->Close();
    }
}

bool Server::Shutdown()
{
    return m_ServerSocket->Close();
}