/*
** EPITECH PROJECT, 2023
** jetpack2Tek3
** File description:
** main
*/

#include "include.hpp"
#include <Parsing.hpp>
#include <Command.hpp>
#include <Game.hpp>
#include <Exception.hpp>
#include <Init.hpp>

void errorArgs(int ac)
{
    if (ac != 7 && ac != 9)
        throw UsageError();
}

int main(int ac, char **av) {
    Server serv;
    Parsing parsing;
    Init init;
    try {
        errorArgs(ac);
        parsing.initParams(ac, av, serv);
        if (!parsing.checkParams(serv))
            return 84;
        init.initServer(serv);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}
