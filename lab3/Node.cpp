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

Node::Node(const Node& other)
    : parent(nullptr)
    , maxChildrenCount(other.maxChildrenCount)
{
    for (const Node* childNode : other.children) {
        Node* newChild = childNode->clone();
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

std::set<std::string> Node::getVariables(std::set<std::string>& variables)
{
    for (Node* childNode : children) {
        VariableNode* variableNode = dynamic_cast<VariableNode*>(childNode);
        if (variableNode != nullptr) {
            variables.insert(variableNode->name);
        }
    }

    return variables;
}

double Node::calculateValue(std::map<std::string, double>& variableValues)
{
    return 1.0;
}

// OPERATOR

OperatorNode::OperatorNode(Operation op)
    : Node(getMaxChildrenCountForOperation(op))
    , operation(op)
{
}

OperatorNode::OperatorNode(Node* parent, Operation op)
    : Node(getMaxChildrenCountForOperation(op), parent)
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

double OperatorNode::calculateValue(std::map<std::string, double>& variableValues)
{
    if (operation == plus) {
        return children[0]->calculateValue(variableValues) + children[1]->calculateValue(variableValues);
    } else if (operation == minus) {
        return children[0]->calculateValue(variableValues) - children[1]->calculateValue(variableValues);
    } else if (operation == multiply) {
        return children[0]->calculateValue(variableValues) * children[1]->calculateValue(variableValues);
    } else if (operation == divide) {
        return children[0]->calculateValue(variableValues) / children[1]->calculateValue(variableValues);
    } else if (operation == sin_op) {
        return sin(children[0]->calculateValue(variableValues));
    } else if (operation == cos_op) {
        return cos(children[0]->calculateValue(variableValues));
    }

    return 1.0;
}

Node* OperatorNode::clone() const
{
    return new OperatorNode(*this);
}

int OperatorNode::getMaxChildrenCountForOperation(Operation op) const
{
    if (op == plus || op == minus || op == multiply || op == divide) {
        return 2;
    } else if (op == sin_op || op == cos_op) {
        return 1;
    } else {
        return 0;
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

std::string VariableNode::toString(std::string& acc)
{
    acc += name;
    acc += " ";

    for (Node* childNode : children) {
        childNode->toString(acc);
    }

    return acc;
}

double VariableNode::calculateValue(std::map<std::string, double>& variableValues)
{
    return variableValues.at(name);
}

Node* VariableNode::clone() const
{
    return new VariableNode(*this);
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

double NumberNode::calculateValue(std::map<std::string, double>& variableValues)
{
    return value;
}

Node* NumberNode::clone() const
{
    return new NumberNode(*this);
}
