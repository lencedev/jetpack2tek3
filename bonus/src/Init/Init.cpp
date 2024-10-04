/*
** EPITECH PROJECT, 2023
** JetPack
** File description:
** Init
*/

#include "Init.hpp"
#include "Command.hpp"
#include "Exception.hpp"
#include "Game.hpp"
#include "include.hpp"

void Init::attemptBind(Server &serv) {
    sockaddr_in s_adr;
    s_adr.sin_family = AF_INET;
    s_adr.sin_port = htons(serv.port);
    s_adr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serv.servfd, reinterpret_cast<struct sockaddr*>(&s_adr), sizeof(s_adr)) == -1)
        throw BindError();
}

void Init::startListen(Server &serv) {
    if (listen(serv.servfd, 2) == -1)
        throw ListenError();
}

void Init::serverInitializationLoop(Server &serv, Game &gameInstance, fd_set &activeFds, int &maxfd) {
    while (!serv.startGame) {
        FD_ZERO(&activeFds);
        FD_SET(serv.servfd, &activeFds);
        maxfd = serv.handleConnection(serv,maxfd, &activeFds);
        if (select(maxfd + 1, &activeFds, NULL, NULL, NULL) == -1)
            throw SelectFailError();
        if (FD_ISSET(serv.servfd, &activeFds) > 0)
            serv.acceptClients(serv);
        serv.executeCmd(serv, &activeFds);
    }
}

void Init::gameExecution(Server &serv, Game &gameInstance) {
    gameInstance.gameLoop(serv);
}

void Init::serverLoop(Server &serv)
{
    Game gameInstance;
    fd_set activeFds;
    int maxfd = 0;

    serverInitializationLoop(serv, gameInstance, activeFds, maxfd);
    gameExecution(serv, gameInstance);
}

void Init::initServer(Server &serv) {
    std::cout << "Init server..." << std::endl;
    std::cout << "Server started on " << serv.port << std::endl;
    serv.servfd = socket(AF_INET, SOCK_STREAM, 0);

    if (serv.servfd == -1)
        throw ServerSetupError();
    FuncPtr functions[] = {&Init::attemptBind, &Init::startListen, &Init::initClients, &Init::serverLoop};
    for (auto function : functions)
        (this->*function)(serv);
}


