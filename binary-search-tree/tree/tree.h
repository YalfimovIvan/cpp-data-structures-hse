#include <memory>

struct tree_node
{
  // Чтобы код собрался на GitHub, используйте этот конструктор в std::make_unique
  explicit tree_node(int val, tree_node *parent = nullptr)
    : value(val), up(parent){};

  int value;
  tree_node *up;
  std::unique_ptr<tree_node> left, right;
};

struct tree
{
  std::unique_ptr<tree_node> root;

  tree_node * insert(int val);
  bool remove(int val);
};