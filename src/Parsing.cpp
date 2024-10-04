#include "include.hpp"

#include <Parsing.hpp>
#include <Server.hpp>
#include <Exception.hpp>

void Parsing::mapConvertion(Server &serv)
{
    int mapWidth = std::stoi(serv.width);
    int mapHeight = std::stoi(serv.height);

    serv.mapArray = std::vector<std::string>(mapHeight);
    for (int i = 0; i < mapHeight; ++i)
        serv.mapArray[i] = serv.map.substr(i * mapWidth, mapWidth);
}

std::string Parsing::readFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open the file.\n";
        return {};
    }
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void Parsing::parseDimensions(Server &serv, const std::string& fileContent)
{
    serv.width = std::to_string(std::distance(fileContent.begin(), std::find(fileContent.begin(), fileContent.end(), '\n')));
    serv.height = std::to_string(std::count(fileContent.begin(), fileContent.end(), '\n') + 1);
    serv.map = fileContent;
    serv.map.erase(std::remove(serv.map.begin(), serv.map.end(), '\n'), serv.map.end());
}

void Parsing::importMap(Server &serv)
{
    std::string fileContent = readFile(serv.mapFile);
    if (fileContent.empty())
        return;
    parseDimensions(serv, fileContent);
    mapConvertion(serv);
}

bool Parsing::checkParams(Server &serv)
{
    struct stat path_stat;

    if (serv.mapFile.empty())
        return false;
    if (stat(serv.mapFile.c_str(), &path_stat) != 0) {
        std::cerr << "Error :Cannot open map file: No such file or directory\n";
        return false;
    }
    if (!S_ISREG(path_stat.st_mode)) {
        std::cerr << "Error :Cannot open map file: Not a file\n";
        return false;
    }
    importMap(serv);
    return true;
}

void Parsing::assign_value(int option, char* optarg, Server &serv)
{
    std::unordered_map<int, std::function<void()>> actions = {
        {'p', [&]() {
            std::string port(optarg);
            try {
                serv.port = std::stoi(port);
            } catch (std::invalid_argument const &e) {
                std::cout << "Bad input: std::invalid_argument thrown" << '\n';
            } catch (std::out_of_range const &e) {
                std::cout << "Integer overflow: std::out_of_range thrown" << '\n';
            }
        }},
        {'g', [&]() { serv.gravity = optarg; }},
        {'m', [&]() { serv.mapFile = optarg; }}
    };
    auto action = actions.find(option);
    if (action != actions.end()) {
        action->second();
    }
}

void Parsing::initParams(int ac, char **av, Server &serv)
{
    int op = 0;
    struct option long_options[] = {
        {"port", required_argument, NULL, 'p'},
        {"gravity", required_argument, NULL, 'g'},
        {"map", required_argument, NULL, 'm'},
        {NULL, 0, NULL, 0}
    };
    while ((op = getopt_long(ac, av, "p:g:m:", long_options, NULL)) != -1)
        assign_value(op, optarg, serv);
}
