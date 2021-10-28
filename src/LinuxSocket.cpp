#include "LinuxSocket.h"

#include <cstring>
#include <iostream>

namespace Prism
{

LinuxSocket::LinuxSocket(const std::string& ipAddress, int port, ISocket::Type type)
    : m_Type(type), m_IPAddress(ipAddress), m_Port(port)
{
    if (m_Type == ISocket::Type::IPV4)
    {
        m_SocketID = socket(AF_INET, SOCK_STREAM, 0);
    }
    else if (m_Type == ISocket::Type::IPV6)
    {
        m_SocketID = socket(AF_INET6, SOCK_STREAM, 0);
    }
}

LinuxSocket::LinuxSocket(int socketID, const std::string& ipAddress, int port, ISocket::Type type)
    : m_SocketID(socketID), m_Type(type), m_IPAddress(ipAddress), m_Port(port)
{
}

LinuxSocket::~LinuxSocket()
{
    close(m_SocketID);
}

bool LinuxSocket::Bind()
{
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));

    if (m_Type == ISocket::Type::IPV4)
    {
        server_addr.sin_family = AF_INET;
    }
    else if (m_Type == ISocket::Type::IPV6)
    {
        server_addr.sin_family = AF_INET6;
    }

    if (m_IPAddress == "") 
    {
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    }

    server_addr.sin_port = htons(m_Port);

    if (bind(m_SocketID, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1) 
    {
        return false;
    }

    return true;
}

bool LinuxSocket::Listen()
{
    if (listen(m_SocketID, 50) == -1)
    {
        return false;
    }

    return true;
}

std::unique_ptr<ISocket> LinuxSocket::Accept()
{
    sockaddr_in clientAddress;
    socklen_t clientAddressSize;
    int clientSocket = accept(m_SocketID, (struct sockaddr*) &clientAddress, &clientAddressSize);

    ISocket::Type type = ISocket::Type::IPV4;
    if (clientAddress.sin_family == AF_INET6)
    {
        type = ISocket::Type::IPV6;
    }

    char clientAddressBuffer[32]; // Used to store the string representation of the socket ip address.
    memset(&clientAddressBuffer, 0, sizeof(clientAddressBuffer));

    if (type == ISocket::Type::IPV4)
    {
        inet_ntop(AF_INET, &clientAddress.sin_addr.s_addr, clientAddressBuffer, sizeof(clientAddressBuffer));
    }
    else if (type == ISocket::Type::IPV6)
    {
        inet_ntop(AF_INET6, &clientAddress.sin_addr.s_addr, clientAddressBuffer, sizeof(clientAddressBuffer));
    }

    return std::make_unique<LinuxSocket>(clientSocket, clientAddressBuffer, (int) clientAddress.sin_port, type);
}

int LinuxSocket::Read(char* buffer, size_t size)
{
    return read(m_SocketID, (void*) buffer, size);
}

int LinuxSocket::Write(const HttpResponse& response)
{
    return write(m_SocketID, response.ToString().c_str(), response.ToString().length());
}

bool LinuxSocket::Close()
{
    if (close(m_SocketID) == -1) {
        return false;
    }
    return true;
}

}