#ifndef COMMAND_H
#define COMMAND_H
#include "Type.h"
#include <string>
#include <iostream>

class Command {
    std::string _parseInputNumber(std::string);
    
    public:
    Type type;
    int multiplier;
    std::string secondArg;

    Command();
    Command(Type);
    ~Command();
    friend std::istream& operator>>(std::istream&, Command&);
};

#endif