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

std::string OperatorNode::ToString()
{
    if (operation == plus) {
        return "+";
    } else if (operation == minus) {
        return "-";
    } else if (operation == multiply) {
        return "*";
    } else if (operation == divide) {
        return "/";
    } else if (operation == sin_op) {
        return "sin";
    } else if (operation == cos_op) {
        return "cos";
    }
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

std::string VariableNode::ToString()
{
    return name;
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

std::string NumberNode::ToString()
{
    return std::to_string(value);
}
