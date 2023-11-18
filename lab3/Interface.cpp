#include "Interface.h"

void runInterface()
{
    Tree tree;
    bool isCorrect;
    std::string input = "start";

    while (input != "quit" && input != "exit") {
        // Get user input and transform it to lowercase
        std::cout << "Waiting for user input:" << std::endl;
        std::getline(std::cin, input);
        input = toLowercase(input);

        // Split command and parameters
        // TODO: no params bug
        std::istringstream iss(input);
        std::string command, params;

        iss >> command;

        std::getline(iss, params);
        params.erase(params.find_first_not_of(" \t"));

        // TODO : export strings to .h
        // Execute user input
        if (command == "enter") {
            tree = Tree(params, isCorrect);
            if (!isCorrect) {
                std::cout << "Error: Formula is not correct. Expression will be corrected.";
            }
            std::cout << "Processing formula: " + tree.toString() << std::endl;

        } else if (command == "vars") {
            for (std::string variable : tree.getVariables()) {
                std::cout << variable + " ";
            }
            std ::cout << std::endl;

        } else if (command == "comp") {
           
        } else if (command == "join") {
            // TODO
        } else {
            std::cout << "" << std::endl;
        }
    }
}

std::string toLowercase(std::string& input)
{
    int i = 0;
    char c;
    std::string output = "";
    while (input[i]) {
        c = input[i];
        output += char(tolower(c));
        i++;
    }
    std::cout << output;
    return output;
}

std::string strip(std::string& input)
{
    std::string result;

    // Remove leading whitespaces
    size_t startPos = input.find_first_not_of(" \t");
    if (startPos != std::string::npos) {
        input = input.substr(startPos);
    }

    // Remove trailing whitespaces
    size_t endPos = input.find_last_not_of(" \t");
    if (endPos != std::string::npos) {
        input = input.substr(0, endPos + 1);
    }

    // Reduce consecutive spaces to a single space
    bool isSpace = false;
    for (char c : input) {
        if (std::isspace(c)) {
            if (!isSpace) {
                result += ' ';
                isSpace = true;
            }
        } else {
            result += c;
            isSpace = false;
        }
    }

    return result;
}
