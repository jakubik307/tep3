#include "Tree.h"

Tree::Tree()
{
    root = new NumberNode(1);
}

Tree::Tree(Node* root)
    : root(root)
{
}

Tree::Tree(std::vector<std::string>& formula, bool& isCorrect)
{
    isCorrect = true;

    std::vector<std::string>::iterator it = formula.begin();
    root = parseFormula(it, formula.end(), isCorrect);

    if (it != formula.end()) {
        // If there are elements remaining in the vector, the formula is incorrect
        isCorrect = false;
    }
}

Tree::Tree(Tree const& other)
{
    copy(other);
}

Tree::~Tree()
{
    delete root;
}

Tree Tree::operator+(const Tree& other) const
{
    Tree result(*this);

    // Find the first leaf node with no children
    Node* leafNode = result.root;
    while (leafNode != nullptr && !leafNode->children.empty()) {
        leafNode = leafNode->children.front();
    }

    if (leafNode != nullptr) {
        Tree copyOfOther(other);

        copyOfOther.root->parent = leafNode->parent;
        if (leafNode->parent != nullptr) {
            for (Node* node : leafNode->parent->children) {
                if (node == leafNode) {
                    node = root->clone();
                }
            }
        }

        delete leafNode;
    }

    return result;
}

Tree& Tree::operator=(const Tree& other)
{
    copy(other);
    return *this;
}

void Tree::copy(Tree const& other)
{
    if (root != nullptr) {
        delete root;
    }

    root = other.root->clone();
}

std::vector<std::string> Tree::getVariables()
{
    std::set<std::string> variablesSet;
    root->getVariables(variablesSet);
    std::vector<std::string> variablesVector(variablesSet.begin(), variablesSet.end());
    return variablesVector;
}

std::string Tree::toString()
{
    std::string acc = "";
    if (root != nullptr) {
        return root->toString(acc);
    } else {
        return "Empty Tree";
    }
}

double Tree::calculateFormula(std::vector<double>& values, bool& isSizeCorrect)
{
    std::vector<std::string> variables = getVariables();

    if (variables.size() != values.size()) {
        isSizeCorrect = false;
        return 0.0;
    } else {
        isSizeCorrect = true;
    }

    std::map<std::string, double> variableValues;

    for (size_t i = 0; i < variables.size(); i++) {
        variableValues[variables[i]] = values[i];
    }

    double result = root->calculateValue(variableValues);

    return result;
}

Node* Tree::parseFormula(std::vector<std::string>::iterator& it, const std::vector<std::string>::iterator& end, bool& isCorrect)
{
    if (it == end) {
        // Empty token, not a valid formula
        isCorrect = false;
        return nullptr;
    }

    std::string token = *it;
    it++;

    if (isdigit(token[0])) {
        // Token is a number
        return new NumberNode(std::stod(token));
    } else if (isalpha(token[0])) {
        // Token is a variable or function
        if (token == "sin" || token == "cos") {
            OperatorNode* opNode = new OperatorNode(getOperationType(token));
            opNode->addChild(parseFormula(it, end, isCorrect)); // Parse operand
            return opNode;
        } else {
            return new VariableNode(token);
        }
    } else if (token == "+" || token == "-" || token == "*" || token == "/") {
        // Token is a binary operator
        OperatorNode* opNode = new OperatorNode(getOperationType(token));
        opNode->addChild(parseFormula(it, end, isCorrect)); // Parse left child
        opNode->addChild(parseFormula(it, end, isCorrect)); // Parse right child
        return opNode;
    } else {
        isCorrect = false;
        return new NumberNode(1);
    }
}

Operation Tree::getOperationType(const std::string& op)
{
    if (op == "+") {
        return plus;
    } else if (op == "-") {
        return minus;
    } else if (op == "*") {
        return multiply;
    } else if (op == "/") {
        return divide;
    } else if (op == "sin") {
        return sin_op;
    } else if (op == "cos") {
        return cos_op;
    } else {
        return plus;
    }
}