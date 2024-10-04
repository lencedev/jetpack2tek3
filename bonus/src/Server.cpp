#include <stdio.h>
#include <stdlib.h>
#include "include.hpp"
#include "Game.hpp"
#include "Command.hpp"
#include "Exception.hpp"
#include "Init.hpp"

int Server::handleConnection(Server &serv, int maxFd, fd_set *activeFds)
{
    maxFd = serv.servfd;
    for (int i = 0; i < 2; i++) {
        if (serv.clients[i].clientSocket == 0)
            continue;
        FD_SET(serv.clients[i].clientSocket, activeFds);
        if (serv.clients[i].clientSocket > maxFd)
            maxFd = serv.clients[i].clientSocket;
    }
    return maxFd;
}

void Server::rejectNewClient(Server &serv) {
    struct sockaddr_in clientAddress;
    socklen_t address_size = sizeof(clientAddress);
    int newClient = accept(serv.servfd, (struct sockaddr *)&clientAddress, &address_size);
    if (newClient == -1)
        throw AcceptFailError();
    serv.servReply(newClient, "Connection rejected, already 2 players logged in.\n");
    close(newClient);
}

void Server::addNewClient(Server &serv) {
    struct sockaddr_in clientAddress;
    socklen_t address_size = sizeof(clientAddress);
    int newClient = accept(serv.servfd, (struct sockaddr *)&clientAddress, &address_size);
    if (newClient == -1)
        throw AcceptFailError();

    std::cout << "A new client has connected from "
              << inet_ntoa(clientAddress.sin_addr) << ":"
              << ntohs(clientAddress.sin_port) << "\n";

    for (int i = 0; i < 2; i++) {
        if (serv.clients[i].clientSocket == 0) {
            serv.clients[i].clientSocket = newClient;
            serv.clientConnected++;
            break;
        }
    }
}

void Server::acceptClients(Server &serv) {
    if (serv.clientConnected == 2)
        rejectNewClient(serv);
    else
        addNewClient(serv);
}

void Server::servReply(int serv, const std::string& msg)
{
    ssize_t bytesSent = send(serv, msg.c_str(), msg.size(), 0);
    if (bytesSent == -1) {
        std::string errMsg = "Failed to send data: " + std::string(strerror(errno));
        throw std::runtime_error(errMsg);
    }
    else if (bytesSent < msg.size())
        std::cerr << "Warning: Not all data was sent to client." << std::endl;
}

void Server::executeCmd(Server &serv, fd_set *activeFds)
{
    Init init;
    for (int i = 0; i < 2; i++)
        if (FD_ISSET(serv.clients[i].clientSocket, activeFds) > 0)
            init.manageClient(serv, serv.clients[i]);
}
