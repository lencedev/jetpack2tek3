/*
** EPITECH PROJECT, 2023
** B-SYN-400-MPL-4-1-jetpack2tek3-owen1.bolling
** File description:
** GameCollision
*/

#include "include.hpp"

#include "Game.hpp"
#include <Deltatime.hpp>
#include "Command.hpp"


void Game::sendFinishUpdate(Server &server, int winnerId) const {
    std::stringstream ss;
    ss << "FINISH " << server.clients[winnerId].ID << "\n";
    std::string response = ss.str();
    for (int idx = 0; idx < 2; idx++)
        server.servReply(server.clients[idx].clientSocket, response.c_str());
    server.stop = 1;
}

int Game::verifyEnemyEncounter(Server &server, int clientId) {
    bool enemyEncounteredPlayer1 = server.clients[0].playerPos == 'e';
    bool enemyEncounteredPlayer2 = server.clients[1].playerPos == 'e';

    if (enemyEncounteredPlayer1 || enemyEncounteredPlayer2) {
        if (enemyEncounteredPlayer1 && enemyEncounteredPlayer2) {
            sendFinishUpdate(server, -1);
        } else {
            int victoriousId = enemyEncounteredPlayer1 ? 1 : 0;
            sendFinishUpdate(server, victoriousId);
        }
    }
    return 0;
}

auto Game::checkCollision(Server &serv, const int clientIndex) -> int {
    if (verifyEnemyEncounter(serv, clientIndex) == 1)
        return 1;
    return verifyCoinCollection(serv, clientIndex);
}

bool Game::checkCollisionsAndSleep(Server &serv, double sleepTime)
{
    if (checkCollision(serv, 0) || checkCollision(serv, 1))
        return true;
    usleep(sleepTime);
    return false;
}
