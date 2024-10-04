/*
** EPITECH PROJECT, 2023
** jetpack2Tek3
** File description:
** client_connection
*/

#include "include.hpp"

#include "Game.hpp"
#include <Deltatime.hpp>
#include "Command.hpp"

int Game::calculatePlayerPosY(const Server &server, int clientId) const {
    return (std::stoi(server.height) - 1) - static_cast<int>(std::round(server.clients[clientId].y));
}

std::string Game::readFromClient(Server &serv, int id) {
    char buffer[2048];
    ssize_t bytesRead = read(serv.clients[id].clientSocket, buffer, sizeof(buffer));
    if (bytesRead > 0)
        return std::string(buffer);
    return "";
}

void Game::processCommands(Server &serv, int id, const std::string &buffer, Command &cmd) {
    std::string token;
    std::istringstream tokenStream(buffer);
    while (std::getline(tokenStream, token)) {
        if (token.empty()) continue;
        cmd.fire(serv, id, token);
    }
}

void Game::handleInputAndCommands(Server &serv, int id) {
    Command cmd;
    std::string buffer = readFromClient(serv, id);
    if (!buffer.empty()) {
        processCommands(serv, id, buffer, cmd);
    }
}

void Game::blockSock(int serv) {
    int fg = fcntl(serv, F_GETFL, 0);

    fcntl(serv, F_SETFL, fg | O_NONBLOCK);
    return;
}

void Game::gameLoop(Server &serv) {
    Command commandInstance;
    struct timeval time1;
    double playerVelocity = 4.0;

    double sleepTime = 1000.0 / 60.0;

    blockSock(serv.clients[0].clientSocket);
    blockSock(serv.clients[1].clientSocket);
    gettimeofday(&time1, NULL);

    while (true)
        processPlayerActions(serv, playerVelocity, commandInstance, sleepTime, time1);
}
