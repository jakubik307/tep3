#pragma once
#include <cctype>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

const double DEFAULT_VALUE = 1;

const enum Operation {
    plus,
    minus,
    multiply,
    divide,
    sin_op,
    cos_op
};

class Node {
public:
    Node(int maxChildrenCount);
    Node(int maxChildrenCount, Node* parent);
    Node(const Node& other);
    virtual ~Node();
    bool addChild(Node* child);
    int getChildrenCount();
    virtual std::string toString(std::string& acc) = 0;
    std::set<std::string> getVariables(std::set<std::string>& variables);
    double calculateValue(std::map<std::string, double>& variableValues);

private:
    Node* parent;
    int maxChildrenCount;
    std::vector<Node*> children;
    virtual Node* clone() const = 0;

    friend class Tree;
    friend class OperatorNode;
    friend class VariableNode;
    friend class NumberNode;
};

class OperatorNode : public Node {
public:
    OperatorNode(Operation op);
    OperatorNode(Node* parent, Operation op);
    std::string toString(std::string& acc) override;
    double calculateValue(std::map<std::string, double>& variableValues);

private:
    Operation operation;

    Node* clone() const override;
    int getMaxChildrenCountForOperation(Operation op) const;

    friend class Tree;
    friend class Node;
};

class VariableNode : public Node {
public:
    VariableNode(std::string name);
    VariableNode(Node* parent, std::string name);
    std::string toString(std::string& acc) override;
    double calculateValue(std::map<std::string, double>& variableValues);

private:
    std::string name;

    Node* clone() const override;

    friend class Tree;
    friend class Node;
};

class NumberNode : public Node {
public:
    NumberNode(double value);
    NumberNode(Node* parent, double value);
    std::string toString(std::string& acc) override;
    double calculateValue(std::map<std::string, double>& variableValues);

private:
    double value;

    Node* clone() const override;

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
    Node* parseFormula(std::istringstream& iss, bool& isCorrect);
    Operation getOperationType(const std::string& op);
};