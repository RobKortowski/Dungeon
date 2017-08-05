#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>

class Interpreter {
public:
    Interpreter();
    ~Interpreter();
    std::string interpret(std::string);
};

#endif
