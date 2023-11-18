#pragma once
#include <set>
#include <string>
#include <vector>
#include <map>

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
    Node(const Node& other);
    virtual ~Node();
    bool addChild(Node* child);
    int getChildrenCount();
    std::string toString(std::string& acc);
    std::set<std::string> getVariables(std::set<std::string>& variables);

private:
    Node* parent;
    int maxChildrenCount;
    std::vector<Node*> children;

    friend class Tree;
    friend class OperatorNode;
    friend class VariableNode;
    friend class NumberNode;
};

class OperatorNode : public Node {
public:
    OperatorNode(Operation op);
    OperatorNode(Node* parent, Operation op);
    std::string toString(std::string& acc);

private:
    Operation operation;

    friend class Tree;
};

class VariableNode : public Node {
public:
    VariableNode(std::string name);
    VariableNode(Node* parent, std::string name);
    std::string toString(std::string& acc);

private:
    std::string name;

    friend class Tree;
    friend class Node;
};

class NumberNode : public Node {
public:
    NumberNode(double value);
    NumberNode(Node* parent, double value);
    std::string toString(std::string& acc);

private:
    double value;

    friend class Tree;
    friend class Node;
};

class Tree {
public:
    Tree();
    Tree(Node* root);
    Tree(std::string& formula, bool& isCorrect);
    Tree(Tree const& other);
    ~Tree();
    Tree operator+(const Tree& other) const;
    Tree& operator=(const Tree& other);

    std::vector<std::string> getVariables();
    std::string toString();
    double calculateFormula(std::vector<double>& values, bool& isSizeCorrect);

private:
    Node* root;

    void copy(Tree const& other);
};