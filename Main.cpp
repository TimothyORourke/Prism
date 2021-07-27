#include "Server.h"

#include <signal.h>

#include <iostream>

static Server server;

void sigint_handler(int signal) {
    if (server.Shutdown()) {
        std::cout << "Server shutdown successful." << std::endl;
    }
    else {
        std::cout << "Server shutdown error." << std::endl;
    }
    exit(EXIT_FAILURE);
}

int main()
{
    signal(SIGINT, sigint_handler);

    server.Run();
}