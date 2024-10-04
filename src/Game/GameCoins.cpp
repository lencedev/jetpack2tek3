#include "Game.hpp"
#include "include.hpp"

void Game::updateGameMap(Server &server, int clientId, int posX, int posY, char newValue) {
    server.mapArray[posY][posX] = newValue;
}

std::string Game::generateCoinMessage(Server &server ,int clientId, int posX, int posY) const {
    std::ostringstream messageStream;
    messageStream << "COIN " << server.clients[clientId].ID << " " << posX << " " << posY << "\n";
    return messageStream.str();
}

void Game::broadcastMessage(Server &server, const std::string& message) const {
    for (auto &client : server.clients)
        server.servReply(client.clientSocket, message.c_str());
}

void Game::increaseScoreAndNotify(Server &server, int clientId, int posX, int posY) const {
    ++server.clients[clientId].score;
    std::string coinMessage = generateCoinMessage(server,clientId, posX, posY);
    broadcastMessage(server, coinMessage);
}

bool Game::checkCoinCollection(Server &server, int clientId) const {
    return server.clients[clientId].playerPos == 'c' || server.clients[clientId].playerPos == (server.clients[clientId].ID == 1 ? 'b' : '1');
}

void Game::updateGamePosition(Server &server, int clientId) {
    int posX = static_cast<int>(std::round(server.clients[clientId].x));
    int posY = calculatePlayerPosY(server, clientId);
    char updatedValue = server.clients[clientId].playerPos == 'c' ? (server.clients[clientId].ID == 1 ? '1' : '2') : '_';

    updateGameMap(server, clientId, posX, posY, updatedValue);
}

int Game::verifyCoinCollection(Server &server, int clientId) {
    if (checkCoinCollection(server, clientId)) {
        int posX = static_cast<int>(std::round(server.clients[clientId].x));
        int posY = calculatePlayerPosY(server, clientId);

        increaseScoreAndNotify(server, clientId, posX, posY);
        updateGamePosition(server, clientId);
    }
    return 0;
}
