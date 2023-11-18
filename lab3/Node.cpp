#include "Tree.h"

// BASE CLASS

Node::Node(int maxChildrenCount)
{
    parent = nullptr;
    this->maxChildrenCount = maxChildrenCount;
    children = std::vector<Node*>();
}

Node::Node(int maxChildrenCount, Node* parent)
{
    this->parent = parent;
    this->maxChildrenCount = maxChildrenCount;
    children = std::vector<Node*>();
}

// TODO: chceck if copying nullptr is okay in all usages
Node::Node(const Node& other)
    : parent(nullptr)
    , maxChildrenCount(other.maxChildrenCount)
{
    for (const Node* childNode : other.children) {
        Node* newChild = new Node(*childNode);
        newChild->parent = this;
        children.push_back(newChild);
    }
}

Node::~Node()
{
    for (Node* childNode : children) {
        delete childNode;
    }
}

bool Node::addChild(Node* child)
{
    if (children.size() < maxChildrenCount) {
        children.push_back(child);
        return true;
    }
    return false;
}

int Node::getChildrenCount()
{
    return children.size();
}

std::string Node::toString(std::string& acc)
{
    return acc;
}

// OPERATOR

OperatorNode::OperatorNode(Operation op)
    : Node(op)
    , operation(op)
{
}

OperatorNode::OperatorNode(Node* parent, Operation op)
    : Node(op, parent)
    , operation(op)
{
}

std::string OperatorNode::toString(std::string& acc)
{
    if (operation == plus) {
        acc += "+";
    } else if (operation == minus) {
        acc += "-";
    } else if (operation == multiply) {
        acc += "*";
    } else if (operation == divide) {
        acc += "/";
    } else if (operation == sin_op) {
        acc += "sin";
    } else if (operation == cos_op) {
        acc += "cos";
    }

    acc += " ";

    for (Node* childNode : children) {
        childNode->toString(acc);
    }

    return acc;
}

// VARIABLE

VariableNode::VariableNode(std::string name) 
    : Node(0)
    , name(name)
{
}

VariableNode::VariableNode(Node* parent, std::string name)
    : Node(0, parent)
    , name(name)
{
}

std::string VariableNode::toString(std::string& acc)
{
    acc += name;
    acc += " ";

    for (Node* childNode : children) {
        childNode->toString(acc);
    }

    return acc;
}

// NUMBER

NumberNode::NumberNode(double value)
    : Node(0)
    , value(value)
{
}

NumberNode::NumberNode(Node* parent, double value)
    : Node(0, parent)
    , value(value)
{
}

std::string NumberNode::toString(std::string& acc)
{
    acc += std::to_string(value);
    acc += " ";

    for (Node* childNode : children) {
        childNode->toString(acc);
    }

    return acc;
}