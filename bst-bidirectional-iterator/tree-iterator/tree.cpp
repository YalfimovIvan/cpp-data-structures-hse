#include "tree.hpp"
#include <cassert>
namespace
{
    tree_node* current_root = nullptr;

    tree_node* leftmost(tree_node* n)
    {
        while (n && n->left) n = n->left.get();
        return n;
    }

    tree_node* rightmost(tree_node* n)
    {
        while (n && n->right) n = n->right.get();
        return n;
    }
}
tree::iterator& tree::iterator::operator++()
{
    assert(p && "operator++ called on end()");
    if (p->right)
    {
        p = leftmost(p->right.get());
        return *this;
    }

    tree_node* cur = p;
    while (cur->up && cur == cur->up->right.get())
        cur = cur->up;

    p = cur->up;
    return *this;
}

tree::iterator& tree::iterator::operator--()
{
    if (p == nullptr)
    {
        p = rightmost(current_root);
        return *this;
    }
    if (p->left)
    {
        p = rightmost(p->left.get());
        return *this;
    }

    tree_node* cur = p;
    while (cur->up && cur == cur->up->left.get())
        cur = cur->up;

    p = cur->up; 
    return *this;
}
tree::iterator tree::iterator::operator++(int)
{
    auto tmp = *this;
    ++*this;
    return tmp;
}

tree::iterator tree::iterator::operator--(int)
{
    auto tmp = *this;
    --*this;
    return tmp;
}

tree::iterator tree::begin() const
{
    current_root = root.get();                 
    return { leftmost(root.get()) };           
}

tree::iterator tree::end() const
{
    current_root = root.get();                 
    return { nullptr };                        
}