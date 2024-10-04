/*
** EPITECH PROJECT, 2023
** JetPack
** File description:
** Parsing
*/

#ifndef PARSING_HPP_
#define PARSING_HPP_
#include <include.hpp>

class Parsing {
    public:
        void importMap(Server &serv);
        void assign_value(int option, char* optarg, Server &serv);
        bool checkParams(Server &serv);
        void initParams(int ac, char **av, Server &serv);
        void mapConvertion(Server &serv);
        void parseDimensions(Server &serv, const std::string& fileContent);
        std::string readFile(const std::string& filename);

    protected:
    private:
};

#endif /* !PARSING_HPP_ */
