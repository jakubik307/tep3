#include "Interface.h"

void runInterface()
{
    Tree tree;
    bool isCorrect;
    std::string input = "start";
    std::vector<std::string> params;

    while (input != "quit" && input != "exit") {
        // Get user input
        std::cout << "Waiting for user input:" << std::endl;
        std::getline(std::cin, input);

        // Input preprocessing
        input = toLowercase(input);
        input = strip(input);
        bool noUnsupportedCharacters;
        input = removeNonOperators(input, noUnsupportedCharacters);
        if (!noUnsupportedCharacters) {
            std::cout << "Unsupported characters detected - they have been removed from input." << std::endl;
            std::cout << "Processed input: " << input << std::endl;
        }

        // Process input
        if (!input.empty()) {
            std::istringstream iss(input);
            std::string command;

            iss >> command;

            // Read the rest of the parameters into a vector
            params.clear();
            while (iss) {
                std::string param;
                iss >> param;
                if (!param.empty()) {
                    params.push_back(param);
                }
            }

            // Params preprocessing
            for (std::string param : params) {
                param = fixDotsInNumbers(param);
            }

            // TODO : export strings to .h
            if (command == "enter") {
                if (params.empty()) {
                    std::cout << "Error: No formula given" << std::endl;
                } else {
                    tree = Tree(params, isCorrect);
                    if (!isCorrect) {
                        std::cout << "Error: Formula is not correct. Expression will be corrected." << std::endl;
                        std::cout << "Processing formula: " + tree.toString() << std::endl;
                    }
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
                bool matchingSize;
                // double result = tree.calculateFormula(params, matchingSize);
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

std::string removeNonOperators(const std::string& input, bool& isCorrect)
{
    std::string result;

    for (char ch : input) {
        if (std::isalnum(ch) || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ' ' || ch == '.') {
            result += ch;
        }
    }

    isCorrect = result == input;
    return result;
}

std::string fixDotsInNumbers(const std::string& input)
{
    std::string result;

    if (input[0] == '.') {
        result += "0";
    }

    bool firstDot = false;

    for (char c : input) {
        if (c == '.') {
            if (!firstDot) {
                firstDot = true;
            }
        } else {
            result += c;
            firstDot = false;
        }
    }

    return result;
};
