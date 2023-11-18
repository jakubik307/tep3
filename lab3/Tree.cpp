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
    Tree result(*this);

    // Find the first leaf node with no children
    Node* leafNode = result.root;
    while (leafNode != nullptr && !leafNode->children.empty()) {
        leafNode = leafNode->children.front();
    }

    if (leafNode != nullptr) {
        Tree copyOfOther(other);

        delete leafNode;

        *leafNode = *copyOfOther.root;
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

std::set<std::string> Tree::getVariables()
{
    std::set<std::string> variables;
    getVariablesRecursive(root, variables);
    return variables;
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
    // TODO: implement this
    return 0.0;
}

std::set<std::string> Tree::getVariablesRecursive(Node* currentNode, std::set<std::string>& variables)
{
    // Rewrite as recursive node function 
    if (currentNode == nullptr) {
        return variables;
    }

    for (Node* childNode : currentNode->children) {
        VariableNode* variableNode = dynamic_cast<VariableNode*>(currentNode);
        if (dynamic_cast<VariableNode*>(currentNode) != nullptr) {
            variables.insert(variableNode->name);
        }
    }
}
