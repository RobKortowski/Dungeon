#include "util/Interpreter.h"
#include <iostream>
#include "util/Dbg.h"

using namespace std;

Interpreter::Interpreter() {
}

Interpreter::~Interpreter() {
}

string Interpreter::interpret(string command) {
    DBG::sig("interpreting: " + command);
    if (command == "hi") {
	DBG::sig("Hello received");
        return "hi";
    }
    return "sup";
}
