/*
** EPITECH PROJECT, 2023
** JetPack
** File description:
** Command
*/
#include "include.hpp"

#include <Command.hpp>
#include <Server.hpp>

void Command::commands(Server &serv, ClientData &clientData, char *buff)
{
    idCommand(serv, clientData, buff);
    map(serv, clientData, buff);
    ready(serv, clientData, buff);
}

void Command::idCommand(Server &serv, ClientData &clientData, const std::string& buff)
{
    const std::string playerCommand = "ID";

    if (buff != playerCommand)
        return;
    int clients = std::accumulate(begin(serv.clients), end(serv.clients), 0,
        [](int count, const ClientData& client) { return count + (client.clientSocket != 0); });
    clientData.ID = clients == 1 ? 1 : 2;
    std::ostringstream responseStream;
    responseStream << "ID " << clientData.ID << "\n";
    serv.servReply(clientData.clientSocket, responseStream.str().c_str());
}


void Command::map(Server &serv, ClientData &clientData, const std::string& buff)
{
    const std::string playerCommand = "MAP";
    std::string cmdResponse;
    if (buff != playerCommand)
        return;
    cmdResponse = "MAP " + std::string(serv.gravity) + " " + std::string(serv.width) + " " + std::string(serv.height) + " " + std::string(serv.map) + "\n";
    serv.servReply(clientData.clientSocket, cmdResponse.c_str());
}

void Command::fire(Server &serv, int id, const std::string& buff)
{
    const std::string playerCommand = "FIRE";
    if (buff.find(playerCommand) != 0)
        return;
    if (buff == "FIRE 0")
        serv.clients[id].jetPack = 0;
    else if (buff == "FIRE 1")
        serv.clients[id].jetPack = 1;
    player(serv, id);
}

void Command::player(Server &serv, int i)
{
    if (serv.stop)
        return;
    std::ostringstream responseStream;
    responseStream << "PLAYER " << serv.clients[i].ID << " "
        << std::fixed << std::setprecision(1) << serv.clients[i].x << " "
        << serv.clients[i].y << " " << serv.clients[i].score << " "
        << serv.clients[i].jetPack << "\n";

    std::string response = responseStream.str();
    for (auto &client : serv.clients)
        serv.servReply(client.clientSocket, response.c_str());
}

void Command::ready(Server &server, ClientData &clientData, const std::string& buffer)
{
    static const std::string command = "READY";
    if (buffer != command)
        return;
    clientData.ready = 1;
    int readyClients = std::count_if(server.clients.begin(), server.clients.end(), [](const ClientData& client) {
        return client.ready == 1;
    });
    if (readyClients == 2) {
        for (auto& clientData : server.clients)
            server.servReply(clientData.clientSocket, "START\n");
        server.startGame = true;
    }
}
