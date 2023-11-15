#include "Tree.h"

Tree::Tree(std::string formula)
{

}

Tree::Tree(Tree const& other)
{
    copy(other);
}

Tree::~Tree()
{
    // TODO: this is probably a memory leak: FIX
    delete root;
}

Tree Tree::operator+(const Tree& other) const
{
    return Tree();
}

Tree& Tree::operator=(const Tree& other)
{
    // TODO: insert return statement here
}

void Tree::copy(Tree const& other)
{
}
