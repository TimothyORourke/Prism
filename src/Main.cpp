#include "Server.h"

#include <signal.h>

#include <iostream>

static Prism::Server server;

void sigint_handler(int signal) 
{
    if (server.Shutdown()) 
    {
        std::cout << "\nServer shutdown successful." << std::endl;
    }
    else 
    {
        std::cout << "\nServer shutdown error." << std::endl;
    }
    exit(EXIT_FAILURE);
}

int main()
{
    signal(SIGINT, sigint_handler);

    server.Run();
}