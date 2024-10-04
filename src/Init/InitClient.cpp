/*
** EPITECH PROJECT, 2023
** B-SYN-400-MPL-4-1-jetpack2tek3-owen1.bolling
** File description:
** InitClient
*/

#include "Init.hpp"
#include "Exception.hpp"

void Init::manageClient(Server &serv, ClientData &clientData)
{
    std::vector<char> buff(2048);
    Command commandInstance;

    ssize_t bytesRead = read(clientData.clientSocket, buff.data(), buff.size());
    if (bytesRead == -1) {
        close(clientData.clientSocket);
        clientData.clientSocket = 0;
        throw FailReceiveData();
    } else if (bytesRead == 0) {
        std::cout << "Client disconnected.\n";
        close(clientData.clientSocket);
        clientData.clientSocket = 0;
        serv.clientConnected--;
        return;
    }

    std::stringstream ss(std::string(buff.begin(), buff.end()));
    std::string token;
    while (std::getline(ss, token, '\n')) {
        token.erase(std::remove(token.begin(), token.end(), '\r'), token.end());
        if (!token.empty()) {
            std::vector<char> nonConstToken(token.begin(), token.end());
            nonConstToken.push_back('\0');
            clientData.buffer = nonConstToken.data();
            commandInstance.commands(serv, clientData, nonConstToken.data());
        }
    }
}

void Init::initClientData(ClientData &clientData) {
    clientData.ready = 0;
    clientData.jetPack = 0;
    clientData.playerPos = '_';
    clientData.score = 0;
    clientData.x = 0.0;
    clientData.y = 0.0;
    clientData.clientSocket = 0;
}

void Init::initClients(Server &serv) {
    serv.clientConnected = 0;
    serv.clients = std::vector<ClientData>(2);
    for (auto &clientData : serv.clients) {
        initClientData(clientData);
    }
}
