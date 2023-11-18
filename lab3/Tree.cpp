#include "Tree.h"

Tree::Tree()
{
    root = new Node(0);
}

Tree::Tree(Node* root)
{
    this->root = root;
}

Tree::Tree(std::string& formula, bool& isCorrect)
{
    // TODO
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
                    node = copyOfOther.root;
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

    root = new Node(*other.root);
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
