#pragma once

#include <vector>;

class Command
{
public:
    virtual void execute() = 0;
    virtual ~Command() {/* std::cout << "CommandDestructor" << std::endl;*/ };
};
