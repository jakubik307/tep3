#pragma once
#include <set>
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
    Node(const Node& other);
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
    std::string ToString();

private:
    Operation operation;

    friend class Tree;
};

class VariableNode : public Node {
public:
    VariableNode(std::string name);
    VariableNode(Node* parent, std::string name);
    std::string ToString();

private:
    std::string name;

    friend class Tree;
};

class NumberNode : public Node {
public:
    NumberNode(double value);
    NumberNode(Node* parent, double value);
    std::string ToString();

private:
    double value;

    friend class Tree;
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

    std::set<std::string> getVariables();
    std::string toString();
    double calculateFormula(std::vector<double>& values, bool& isSizeCorrect);
    Tree joinTrees(std::string& formula);

private:
    Node* root;

    void copy(Tree const& other);
    std::set<std::string> getVariablesRecursive(Node* currentNode, std::set<std::string>& variables);
};