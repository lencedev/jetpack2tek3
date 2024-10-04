/*
** EPITECH PROJECT, 2023
** B-SYN-400-MPL-4-1-jetpack2tek3-owen1.bolling
** File description:
** GameMovements
*/

#include "Game.hpp"

void Game::updateGameState(Server &serv, double movement, Command &commandInstance)
{
    for (auto &clientData : serv.clients) {
        char prev_pos = clientData.playerPos;
        clientData.x += movement;
        clientData.playerPos = serv.mapArray[(std::stoi(serv.height) - 1) - static_cast<int>(std::round(clientData.y))][static_cast<int>(std::round(clientData.x))];
        if (clientData.playerPos != prev_pos)
            clientData.coinMessageSent = false;
        commandInstance.player(serv, 0);
        commandInstance.player(serv, 1);
    }
}

void Game::processPlayerActions(Server &serv, double player_velocity, Command &commandInstance, double sleepTime, struct timeval &time1) {
    double movement = calculateMovement(serv, player_velocity, time1);
    for(int clientId = 0; clientId < 2; ++clientId) {
        handleInputAndCommands(serv, clientId);
        updatePlayerPosition(serv, clientId, movement);
        commandInstance.player(serv, clientId);
    }
    checkCollisionsAndSleep(serv, sleepTime);
}


double Game::calculateMovement(Server &serv, double player_velocity, struct timeval &previousTime) {
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    double elapsedTimeInMilliseconds = (currentTime.tv_sec - previousTime.tv_sec) * 1000.0;
    elapsedTimeInMilliseconds += (currentTime.tv_usec - previousTime.tv_usec) / 1000.0;
    previousTime = currentTime;

    return player_velocity * (elapsedTimeInMilliseconds / 1000.0);
}

void Game::updatePlayerPosition(Server &serv, int clientId, double movement) {
    serv.clients[clientId].x += movement;
    serv.clients[clientId].y = calculateYPosition(serv, clientId);
    serv.clients[clientId].playerPos = serv.mapArray[(std::stoi(serv.height) - 1) - static_cast<int>(std::round(serv.clients[clientId].y))][static_cast<int>(std::round(serv.clients[clientId].x))];
}

double Game::calculateYPosition(Server &serv, int clientId) {
    if (serv.clients[clientId].jetPack)
        return (serv.clients[clientId].y + std::stoi(serv.gravity) * (1.0 / 1800.0)) > (std::stoi(serv.height) - 1) ? (std::stoi(serv.height) - 1) : (serv.clients[clientId].y + std::stoi(serv.gravity) * (1.0 / 1800.0));
    else
        return (serv.clients[clientId].y - std::stoi(serv.gravity) * (1.0 / 1800.0)) < 0 ? 0 : (serv.clients[clientId].y - std::stoi(serv.gravity) * (1.0 / 1800.0));
}
