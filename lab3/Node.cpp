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

Node::~Node()
{
    for (Node* node : children) {
        delete node;
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

OperatorNode::~OperatorNode()
{
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

VariableNode::~VariableNode()
{
    // TODO: check if that shit runs default destructor
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

NumberNode::~NumberNode()
{
    // TODO: check if that shit runs default destructor
}
