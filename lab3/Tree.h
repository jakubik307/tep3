#pragma once
#include <string>
#include <vector>

const double DEFAULT_VALUE = 1;

const enum Operation {
    plus = 2,
    minus = 2,
    multiply = 2,
    divide = 2,
    sin_op = 1,
    cos_op = 1
};

class Node {
public:
    Node(int maxChildrenCount);
    Node(int maxChildrenCount, Node* parent);
    virtual ~Node();
    bool addChild(Node* child);
    int getChildrenCount();

private:
    Node* parent;
    int maxChildrenCount;
    std::vector<Node*> children;

    friend class Tree;
};

class OperatorNode : public Node {
public:
    OperatorNode(Operation op);
    OperatorNode(Node* parent, Operation op);
    ~OperatorNode();

private:
    Operation operation;

    friend class Tree;
};

class VariableNode : public Node {
public:
    VariableNode(std::string name);
    VariableNode(Node* parent, std::string name);
    ~VariableNode();

private:
    std::string name;

    friend class Tree;
};

class NumberNode : public Node {
public:
    NumberNode(double value);
    NumberNode(Node* parent, double value);
    ~NumberNode();

private:
    double value;

    friend class Tree;
};

class Tree {
public:
    Tree(std::string formula);
    Tree(Tree const& other);
    ~Tree();
    Tree operator+(const Tree& other) const;
    Tree& operator=(const Tree& other);

private:
    Node* root;
    std::string formula;

    void copy(Tree const& other);
    std::string fixFormula(std::string formula);
};