/*
** EPITECH PROJECT, 2023
** JetPack
** File description:
** Command
*/

#ifndef COMMAND_HPP_
#define COMMAND_HPP_

#include <include.hpp>

class Command {
    public:
        void commands(Server &serv, ClientData &clientData, char *buff);
        void fire(Server &serv, int id, const std::string& buff);
        void idCommand(Server &serv, ClientData &clientData, const std::string& buff);
        void map(Server &serv, ClientData &clientData, const std::string& buff);
        void player(Server &serv, int i);
        void ready(Server &serv, ClientData &clientData, const std::string& buff);

    protected:
    private:
};

#endif /* !COMMAND_HPP_ */
