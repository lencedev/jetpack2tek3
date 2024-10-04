/*
** EPITECH PROJECT, 2023
** JetPack
** File description:
** Server
*/

#ifndef Server_HPP_
#define Server_HPP_

#include <getopt.h>
#include "include.hpp"

class ClientData {
    public:
        int ready;
        bool coinMessageSent;
        int clientSocket;
        int score;
        int ID;
        double x;
        int jetPack;
        double y;
        std::string buffer;
        char playerPos;
        ClientData() : coinMessageSent(false) { }
};

class Server {
    public:
        int servfd;
        int stop;
        int port;
        std::string ms;
        std::string gravity;
        std::string width;
        std::string height;
        int clientConnected;
        std::vector<std::string> mapArray;
        std::string map;
        std::string mapFile;
        int startGame;
        std::vector<ClientData> clients;

        Server() : ms("0"), stop(0), servfd(0), port(0), width("0"), height("0"), gravity("0"), clientConnected(0), map(""), mapFile(""), startGame(0) { }
        int handleConnection(Server &serv, int maxfd, fd_set *activeFds);
        void acceptClients(Server &serv);
        void executeCmd(Server &serv, fd_set *activeFds);
        void addNewClient(Server &serv);
        void servReply(int serv, const std::string &msg);
        void rejectNewClient(Server &serv);
};

#endif /* !Server_HPP_ */
