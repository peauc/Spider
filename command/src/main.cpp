#include <iostream>
#include "Module.h"
#include "Command.h"


int main() {
    Module  module;
    Command command;
    std::string received;

    received.append(0x01);
    command.process(module, received);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}