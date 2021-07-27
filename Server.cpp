#include "Server.h"

#include "Core.h"
#include "HttpResponse.h"
#include "LinuxSocket.h"
#include "HttpRequest.h"
#include "HttpRequestParser.h"

#include <cstring>
#include <iostream>
#include <sstream>

namespace Prism
{

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

        char requestBuffer[MAX_REQUEST_LENGTH];
        memset(&requestBuffer, 0, sizeof(requestBuffer));
        int bytesRead = clientSocket->Read(requestBuffer, MAX_REQUEST_LENGTH);
        
        HttpRequestParser requestParser(requestBuffer);
        HttpRequest request = requestParser.GetRequest();

        std::cout << clientSocket->GetIPAddress() << ":" << clientSocket->GetPort() << " \"";
        std::cout << request.GetMethodText() << " " << request.GetPath() << " " << request.GetVersion() << "\"\n";

        HttpResponse response("<h1>Hi</h1>");
        clientSocket->Write(response);
        clientSocket->Close();
    }
}

bool Server::Shutdown()
{
    return m_ServerSocket->Close();
}

}