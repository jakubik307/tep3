#include "Interface.h"

void runInterface()
{
    Tree tree;
    bool isCorrect;
    std::string input = "start";

    while (input != "quit" && input != "exit") {
        std::cout << "Waiting for user input:" << std::endl;
        std::getline(std::cin, input);
        input = toLowercase(input);
        input = strip(input);

        if (!input.empty()) {
            std::istringstream iss(input);
            std::string command, params;
            params = "";

            iss >> command;

            if (iss) {
                std::getline(iss, params);
                params = strip(params);
            }

            // TODO : export strings to .h
            if (command == "enter") {
                tree = Tree(params, isCorrect);
                if (!isCorrect) {
                    std::cout << "Error: Formula is not correct. Expression will be corrected." << std::endl;
                    std::cout << "Processing formula: " + tree.toString() << std::endl;
                }
            } else if (command == "vars") {
                std::vector<std::string> variables = tree.getVariables();
                if (!variables.empty()) {
                    for (std::string variable : tree.getVariables()) {
                        std::cout << variable + " ";
                    }
                    std ::cout << std::endl;
                } else {
                    std::cout << "No variables in the tree" << std::endl;
                }
            } else if (command == "print") {
                std::cout << tree.toString() << std::endl;
            } else if (command == "comp") {
                // TODO
            } else if (command == "join") {
                Tree newTree = Tree(params, isCorrect);
                if (!isCorrect) {
                    std::cout << "Error: Formula is not correct. Expression will be corrected.";
                    std::cout << "Processing formula: " + newTree.toString() << std::endl;
                }
                tree = tree + newTree;
                std::cout << "Merge successful: " + newTree.toString() << std::endl;

            } else {
                std::cout << "Error: Unknown command." << std::endl;
            }
        } else {
            std::cout << "Error: Empty input. Please enter a valid command." << std::endl;
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
