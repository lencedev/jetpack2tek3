/*
** EPITECH PROJECT, 2023
** JetPack
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <Server.hpp>
#include <Command.hpp>

class Game {
    public:
        void gameLoop(Server &serv);
        auto checkEnemy(Server &serv, const int clientIndex) -> int;
        int checkCoin(Server &serv, int i);
        auto checkCollision(Server &serv, const int clientIndex) -> int;
        bool checkCollisionsAndSleep(Server &serv, double sleepTime);
        void updateGameState(Server &serv, double movement, Command& commandInstance);
        void collectCoin(Server &serv, int x, int y);
        void processPlayerActions(Server &serv, double player_velocity, Command &commandInstance, double sleepTime, struct timeval &t1);
        double calculateMovement(Server &serv, double player_velocity, struct timeval &t1);
        void updatePlayerPosition(Server &serv, int clientId, double movement);
        double calculateYPosition(Server &serv, int clientId);
        void blockSock(int serv);
        void handleInputAndCommands(Server &serv, int id);
        void processCommands(Server &serv, int id, const std::string &buffer, Command &cmd);
        std::string readFromClient(Server &serv, int id);
        void sendCoinUpdate(Server &serv, int i, int playerPosX, int playerPosY) const;
        void updateMapArray(Server &serv, int i, int playerPosX, int playerPosY, char symbol);
        int computePlayerPosition(const Server &serv, int i) const;
        int verifyEnemyEncounter(Server &server, int clientId);
        void sendFinishUpdate(Server &server, int winnerId) const;
        int verifyCoinCollection(Server &server, int clientId);
        void updateGameMap(Server &server, int clientId, int posX, int posY, char newValue);
        void increaseScoreAndNotify(Server &server, int clientId, int posX, int posY) const;
        int calculatePlayerPosY(const Server &server, int clientId) const;
        std::string generateCoinMessage(Server &server, int clientId, int posX, int posY) const;
        void broadcastMessage(Server &server, const std::string& message) const;
        bool checkCoinCollection(Server &server, int clientId) const;
        void updateGamePosition(Server &server, int clientId);

        //void displayFrameRate(Server &serv);

    protected:
    private:
};

#endif /* !GAME_HPP_ */
