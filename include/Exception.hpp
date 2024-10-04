/*
** EPITECH PROJECT, 2023
** JetPack
** File description:
** Exception
*/

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <exception>

class MissingArgumentError : public std::exception {
public:
    const char * what () const throw () {
        return "Error: Missing argument.";
    }
};

class AcceptFailError : public std::exception {
public:
    const char * what () const throw () {
        return "Error: Accept has failed.";
    }
};

class SendDataFail : public std::exception {
public:
    const char * what () const throw () {
        return "Error: Failed to send data";
    }
};

class OpenFileError : public std::exception {
public:
    const char * what () const throw () {
        return "Failed to open the file.";
    }
};

class MapNoSuchFileError : public std::exception {
public:
    const char * what () const throw () {
        return "Cannot open map file: No such file or directory";
    }
};

class SelectFailError : public std::exception {
public:
    const char * what () const throw () {
        return "Select has failed";
    }
};

class FailReceiveData : public std::exception {
public:
    const char * what () const throw () {
        return "Failed to receive data";
    }
};

class BindError : public std::exception {
public:
    const char * what () const throw () {
        return "Bind didn't work";
    }
};

class ListenError : public std::exception {
public:
    const char * what () const throw () {
        return "Listen didn't work";
    }
};

class ServerSetupError : public std::exception {
public:
    const char * what () const throw () {
        return "Server couldn't be setup";
    }
};

class UsageError : public std::exception {
public:
    const char * what () const throw () {
        return "Usage: ./serverJ2T3 -p port -g gravity -m map";
    }
};

#endif /* !EXCEPTION_HPP_ */
