//
// Created by lucas on 26/04/2022.
//

#ifndef QUNIONFIND_TREENODE_HPP
#define QUNIONFIND_TREENODE_HPP

#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <vector>

/**
 * Union Find data structure as tree with additional information in root node of tree
 */
class TreeNode {
public:
    std::size_t                            vertexIdx = 0;
    bool                                   isCheck   = false;
    std::shared_ptr<TreeNode>              parent    = nullptr;
    std::vector<std::shared_ptr<TreeNode>> children{};
    size_t                                 clusterSize = 1;
    std::set<std::size_t>    boundaryVertices{};
    std::set<std::size_t>    checkVertices{};
    // for interior calculation
    std::set<std::size_t> markedNeighbours{};
    bool                  marked = false;

    TreeNode():
        TreeNode(-1) {}

    explicit TreeNode(const std::size_t vertexIdx) {
        this->vertexIdx = vertexIdx;
        this->boundaryVertices.insert(this->vertexIdx);
    }

    /*
 * Recursive find using path compression
 */
    static std::shared_ptr<TreeNode> Find(std::shared_ptr<TreeNode>& node) {
        if (node->parent == nullptr) {
            return node;
        } else {
            node->parent = Find(node->parent);
            return node->parent;
        }
    }
    /*
     * Merge two trees with given roots
     */
    static void Union(std::shared_ptr<TreeNode>& tree1, std::shared_ptr<TreeNode>& tree2) {
        auto root1 = Find(tree1);
        auto root2 = Find(tree2);

        if (*root1 == *root2) {
            return;
        }

        if (root1->clusterSize <= root2->clusterSize) {
            addFirstToSecondTree(root1, root2);
        } else if (root1->clusterSize > root2->clusterSize) {
            addFirstToSecondTree(root2, root1);
        }
    }

    static void addFirstToSecondTree(std::shared_ptr<TreeNode>& first, std::shared_ptr<TreeNode>& second) {
        first->parent = second;
        second->children.emplace_back(first);
        second->clusterSize += first->clusterSize;
        for (const auto& cv: first->checkVertices) {
            second->checkVertices.insert(cv);
        }
        first->checkVertices.clear();
        if (first->isCheck) {
            first->checkVertices.insert(first->vertexIdx);
        }
    }

    /*TreeNode& operator=(const TreeNode& other) {
        if (this == &other) {
            return *this;
        }
        vertexIdx = other.vertexIdx;
        isCheck   = other.isCheck;
        parent = other.parent;
        children = other.children;
        clusterSize      = other.clusterSize;
        boundaryVertices = other.boundaryVertices;
        checkVertices    = other.checkVertices;

        return *this;
    }*/
    bool operator==(const TreeNode& other) const {
        return this->vertexIdx == other.vertexIdx;
    }
    bool operator<(const TreeNode& other) const {
        return this->vertexIdx < other.vertexIdx;
    }

    friend std::ostream& operator<<(std::ostream& os, const TreeNode& v) {
        return os << "idx: " << v.vertexIdx << "parentIx: " << v.parent->vertexIdx << "check: " << v.isCheck << "children: " << v.children;
    }

    friend std::ostream& operator<<(std::ostream& os, const std::set<TreeNode>& v) {
        if (v.empty()) {
            os << "[]";
            return os;
        }
        os << "[";
        for (const auto& i: v) {
            os << i.vertexIdx;
            os << ", ";
        }
        os << "\b\b";
        os << "]";
        return os;
    }
    friend std::ostream& operator<<(std::ostream& os, const std::vector<TreeNode>& v) {
        if (v.empty()) {
            os << "[]";
            return os;
        }
        os << "[";
        for (const auto& i: v) {
            os << i.vertexIdx;
            os << ", ";
        }
        os << "\b\b";
        os << "]";
        return os;
    }
    friend std::ostream& operator<<(std::ostream& os, const std::vector<std::shared_ptr<TreeNode>>& v) {
        if (v.empty()) {
            os << "[]";
            return os;
        }
        os << "[";
        for (const auto& i: v) {
            os << i->vertexIdx;
            os << ", ";
        }
        os << "\b\b";
        os << "]";
        return os;
    }
    friend std::ostream& operator<<(std::ostream& os, const std::set<std::shared_ptr<TreeNode>>& v) {
        if (v.empty()) {
            os << "[]";
            return os;
        }
        os << "[";
        for (const auto& i: v) {
            os << i->vertexIdx;
            os << ", ";
        }
        os << "\b\b";
        os << "]";
        return os;
    }
};

#endif //QUNIONFIND_TREENODE_HPP
