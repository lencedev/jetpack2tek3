/*
** EPITECH PROJECT, 2023
** JetPack
** File description:
** Init
*/

#ifndef INIT_HPP_
#define INIT_HPP_

#include "include.hpp"
#include "Game.hpp"

class Init {
    public:
        void initServer(Server &serv);
        void initClients(Server &serv);
        void manageClient(Server &serv, ClientData &clientData);
        void attemptBind(Server &serv);
        void startListen(Server &serv);
        void serverInitializationLoop(Server &serv, Game &gameInstance, fd_set &activeFds, int &maxfd);
        void gameExecution(Server &serv, Game &gameInstance);
        void serverLoop(Server &serv);
        void initClientData(ClientData &clientData);
        typedef void (Init::*FuncPtr)(Server&);

    private:
};

#endif /* !INIT_HPP_ */
