#include "Server.h"

#include "HttpRequest.h"
#include "HttpRequestParser.h"
#include "HttpResponse.h"
#include "HttpResponseBuilder.h"
#include "LinuxSocket.h"

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

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
    ServerSocketSetup();
    
    while (true)
    {
        auto clientSocket = m_ServerSocket->Accept();
        HttpRequest request = GetClientHttpRequest(clientSocket);

        std::cout << clientSocket->GetIPAddress() << ":" << clientSocket->GetPort() << " \"";
        std::cout << request.GetMethodText() << " " << request.GetPath() << " " << request.GetVersion() << "\" ";

        HandleRequest(request, clientSocket);
    }
}

bool Server::Shutdown()
{
    return m_ServerSocket->Close();
}

void Server::ServerSocketSetup() const
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

    std::cout << "Server listening on port " << m_ServerSocket->GetPort() << "..." << std::endl;
}

HttpRequest Server::GetClientHttpRequest(const std::unique_ptr<ISocket>& clientSocket) const
{
    std::string requestString;

    const unsigned int requestBufferLength = 256;
    char requestBuffer[requestBufferLength];

    unsigned int bytesRead = 0;
    bool endOfRequest = false;
    while (!endOfRequest)
    {
        memset(&requestBuffer, 0, requestBufferLength);

        bytesRead += clientSocket->Read(requestBuffer, requestBufferLength);
        requestString += std::string(requestBuffer);

        if (requestString.find("\r\n\r\n") != std::string::npos)
            endOfRequest = true;

        if (bytesRead >= MAX_REQUEST_LENGTH)
            break;
    }

    HttpRequestParser requestParser(requestString);
    return requestParser.GetRequest();
}

void Server::HandleRequest(const HttpRequest& request, const std::unique_ptr<ISocket>& clientSocket) const
{
    HttpResponse response = HttpResponseBuilder().SetRequestMethod(request.GetMethod())
                            .SetResourcePath(request.GetPath()).Build();

    std::cout << "(" << response.GetResponseHttpVersion() << " " 
              << std::to_string(response.GetResponseCode()) << " " 
              << response.GetStatusText(response.GetResponseCode()) 
              << ")" << std::endl;

    clientSocket->Write(response);
    clientSocket->Close();
}

}