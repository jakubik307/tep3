#include "Interface.h"
#include <iostream>
#include <string.h>

void start()
{
    std::string input = "start";

    while (input != "quit" && input != "exit") {
        // TODO?: pass vector instead of string or process string?
        // TODO: change info message
        std::cout << "Waiting for user input:" << std::endl;
        std::getline(std::cin, input);
        // TODO: implement if
        if (input == "enter") {
            // enter
        } else if (input == "vars") {
            // vars
        } else if (input == "comp") {
            // comp
        } else if (input == "join") {
            // join
        } else {
            // bad input
        }
    }
}
