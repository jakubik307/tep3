#include "Tree.h"

Tree::Tree()
{
    root = nullptr;
}

Tree::Tree(Node* root)
{
    this->root = root;
}

Tree::Tree(std::string& formula, bool& isCorrect)
{
    
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
    // TODO: implement
    return Tree();
}

Tree& Tree::operator=(const Tree& other)
{
    // TODO: check if return is correct
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

std::set<std::string> Tree::getVariables()
{
    std::set<std::string> variables;
    getVariablesRecursive(root, variables);
    return variables;
}

std::string Tree::toString()
{
    // TODO: WORK WITH NODE TO STRING
    return std::string();
}

double Tree::calculateFormula(std::vector<double>& values, bool& isSizeCorrect)
{
    return 0.0;
}

Tree Tree::joinTrees(std::string& formula)
{
    return Tree();
}

std::set<std::string> Tree::getVariablesRecursive(Node* currentNode, std::set<std::string>& variables)
{
    // Rewrite as recursive node function 
    if (currentNode == nullptr) {
        return;
    }

    for (Node* childNode : currentNode->children) {
        VariableNode* variableNode = dynamic_cast<VariableNode*>(currentNode);
        if (dynamic_cast<VariableNode*>(currentNode) != nullptr) {
            variables.insert(variableNode->name);
        }
    }
}
