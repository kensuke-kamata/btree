#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "is_comparable.h"

template <typename T>
class BTreeNode {
 public:
  static_assert(is_comparable<T>::value, "T must be comparable");

  BTreeNode(size_t order, bool isleaf);

  bool HasMaxKeys() const;
  bool HasMaxChildren() const;

  void Traverse(size_t level = 0) const;
  bool Search(T key);

  void Split(size_t index, BTreeNode<T> &parent);

  bool InsertKey(T key);
  bool InsertChild(size_t index, std::unique_ptr<BTreeNode<T>> child);

  bool InsertNonFull(T key);

  std::vector<T> keys_ = {};
  std::vector<std::unique_ptr<BTreeNode<T>>> children_ = {};
  bool isleaf_ = true;
  size_t order_ = 0;
};

/**
 * Constructor
 */
template<typename T>
BTreeNode<T>::BTreeNode(size_t order, bool isleaf) : order_(order), isleaf_(isleaf) {
  if (order < 2) {
    throw std::invalid_argument("'order' must be at least 2");
  }
}

/**
 * Check if the node has the maximum number of keys
 */
template<typename T>
bool BTreeNode<T>::HasMaxKeys() const {
  return keys_.size() == order_ - 1;
}

/**
 * Check if the node has the maximum number of children
 */
template<typename T>
bool BTreeNode<T>::HasMaxChildren() const {
  return children_.size() == order_;
}

/**
 * Insert a key into a node
 */
template<typename T>
bool BTreeNode<T>::InsertKey(T key) {
  if (HasMaxKeys()) {
    return false;
  }
  auto pos = std::lower_bound(keys_.begin(), keys_.end(), key);
  keys_.insert(pos, key);
  return true;
}

/**
 * Insert a child into a node
 */
template<typename T>
bool BTreeNode<T>::InsertChild(size_t index, std::unique_ptr<BTreeNode<T>> child) {
  if (HasMaxChildren()) {
    return false;
  }
  auto pos = children_.begin() + index;
  children_.insert(pos, std::move(child));
  return true;
}

/**
 * Traverse all nodes in a subtree rooted with this node
 */
template<typename T>
void BTreeNode<T>::Traverse(size_t level) const {
  size_t i = 0;
  size_t n = keys_.size();
  std::string indent(level * 4, ' ');

  // Traverse through `n` keys
  std::cout << indent << "Keys: ";
  for (; i < n; i++){
    if (!isleaf_)
      children_[i]->Traverse();
    std::cout << " " << keys_[i];
  }
  std::cout << std::endl;

  // Traverse through `n+1` children
  if (!isleaf_)
    children_[i]->Traverse();
}

/**
 * Search `key` in a subtree rooted with this node
 */
template<typename T>
bool BTreeNode<T>::Search(T key) {
  auto it = std::lower_bound(keys_.begin(), keys_.end(), key);
  auto i  = std::distance(keys_.begin(), it);

  if (it != keys_.end() && *it == key) {
    return true;
  }

  return children_[i]->Search(key);
}

/**
 * Split a child node
 */
template<typename T>
void BTreeNode<T>::Split(size_t index, BTreeNode<T> &parent) {
  size_t mid = (order_ - 1) / 2;

  auto &child = children_[index];
  auto node = std::make_unique<BTreeNode<T>>(order_, child->isleaf_);

  // Move the last (order-1)/2 keys of child to the new node
  {
    size_t n = order_ / 2 - 1;
    for (size_t i = 0; i < n; i++) {
      node->InsertKey(child->keys_[mid + i + 1]);
    }
  }

  // If child is not a leaf, move the last order/2 children of child to the new node
  if (!child->isleaf_) {
    size_t n = order_ / 2;
    for (size_t i = 0; i < n; i++) {
      node->InsertChild(i, std::move(child->children_[mid + i + 1]));
    }
  }

  // Move the middle key up to the parent node
  parent.InsertKey(child->keys_[mid]);

  // Adjust the child pointers of the parent
  parent.InsertChild(index + 1, std::move(node));
}

template<typename T>
bool BTreeNode<T>::InsertNonFull(T key) {
  if (isleaf_) {
    return InsertKey(key);
  }

  auto pos = std::lower_bound(keys_.begin(), keys_.end(), key);
  auto index = std::distance(keys_.begin(), pos);

  auto &child = children_[index];

  // If the child is full, split it
  if (child->HasMaxKeys()) {
    Split(index, *this);

    // After splitting, determine which of the two children to use for the key
    if (keys_[index] < key) {
      index++;
    }
  }

  return children_[index]->InsertNonFull(key);
}


template <typename T>
class BTree {
 public:
  static_assert(is_comparable<T>::value, "T must be comparable");

  /** Constructor */
  BTree(size_t order);

  void Insert(T key);
  void Print();

  bool Search(T key) const;

 private:
  std::unique_ptr<BTreeNode<T>> root_ = nullptr;
  size_t order_ = 0;
};

/**
 * Constructor
 */
template<typename T>
BTree<T>::BTree(size_t order) : order_(order) {
  if (order < 2) {
    throw std::invalid_argument("'order' must be at least 2");
  }
}

template<typename T>
void BTree<T>::Insert(T key) {
  if (root_ == nullptr) {
    root_ = std::make_unique<BTreeNode<T>>(order_, true);
    root_->InsertKey(10);
    return;
  }

  if (root_->HasMaxKeys()) {
    auto node = std::make_unique<BTreeNode<T>>(order_, false);
    node->InsertChild(0, std::move(root_));
    node->Split(0, *node);
    root_ = std::move(node);
    return;
  }

  root_->InsertNonFull(key);
}

template<typename T>
void BTree<T>::Print() {
  if (root_ != nullptr) {
    root_->Traverse();
  }
}

template<typename T>
bool BTree<T>::Search(T key) const {
  if (root_ == nullptr) {
    return false;
  }
  return root_->Search(key);
}
