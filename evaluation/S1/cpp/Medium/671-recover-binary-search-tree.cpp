// Source: https://leetcode.com/problems/recover-binary-search-tree/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary search tree (BST), where the values of exactly two nodes of the tree were swapped by mistake. Recover the tree without changing its structure.
//
// Example:
// Input: root = [1,3,null,null,2]
// Output: [3,1,null,null,2]
// Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3 makes the BST valid.
//
// Constraints:
// The number of nodes in the tree is in the range [2, 1000].
// 	-231 <= Node.val <= 231 - 1
//
//
//  
// Follow up: A solution using O(n) space is pretty straight-forward. Could you devise a constant O(1) space solution?
//
// Helpful references (internal KB):
// - Balanced Search Trees (tree, ds, binary-search, recursion)
//   • When to use: When you need to store a dynamic set of ordered data and require guaranteed logarithmic time complexity for search, insertion, and deletion operations, even in worst-case scenarios.
//   • Idea: Balanced search trees are a class of self-balancing binary search trees that maintain a logarithmic height to ensure O(log N) time complexity for core operations like search, insertion, and deletion. They achieve this balance through structural modifications such as rotations or node splitting/merging.
//   • Invariants: For any node, all keys in its left subtree are less than its key(s), and all keys in its right subtree are greater than its key(s).; The height of the tree is always proportional to log N, ensuring O(log N) operations.
//   • Tips: Understand the specific balancing rules (e.g., AVL rotations, Red-Black tree color properties, 2-3 tree node splits).; Consider the trade-offs between different balanced tree types (e.g., simpler implementation vs. stricter balance).
//   • Pitfalls: Implementation complexity can be high due to intricate rebalancing logic.; Overhead for rebalancing operations might be noticeable for very small N.
// - Prüfer code (tree, heap, simulation, greedy)
//   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
//   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
//   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
//   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
//   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
// - Depth First Search (graph, dfs)
//   • When to use: Use to explore all reachable nodes, find paths, detect cycles, or perform topological sorting. It's also suitable for tree traversals and connected components.
//   • Idea: DFS explores as far as possible along each branch before backtracking. It has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes on the current path from source to current node are marked as visiting.; All nodes already fully explored are marked as visited.
//   • Tips: Use a visited set/array to prevent infinite loops in cyclic graphs.; Recursion stack can lead to stack overflow for deep graphs; consider iterative DFS with an explicit stack.
//   • Pitfalls: Stack overflow with deep recursion on large graphs.; Incorrectly handling visited states can lead to infinite loops or incorrect results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void recoverTree(TreeNode* root) {
        TreeNode *first = nullptr, *second = nullptr, *prev = nullptr;
        TreeNode *current = root;

        while (current) {
            if (!current->left) {
                // Visit current node
                if (prev && prev->val > current->val) {
                    if (!first) first = prev;
                    second = current;
                }
                prev = current;
                current = current->right;
            } else {
                // Find the inorder predecessor of current
                TreeNode* pred = current->left;
                while (pred->right && pred->right != current) {
                    pred = pred->right;
                }

                if (!pred->right) {
                    // Make current the right child of its inorder predecessor
                    pred->right = current;
                    current = current->left;
                } else {
                    // Revert the changes made in the 'if' part to restore the original tree
                    pred->right = nullptr;

                    // Visit current node
                    if (prev && prev->val > current->val) {
                        if (!first) first = prev;
                        second = current;
                    }
                    prev = current;
                    current = current->right;
                }
            }
        }

        // Swap the values of the two nodes to correct the BST
        if (first && second) {
            int temp = first->val;
            first->val = second->val;
            second->val = temp;
        }           
    }
};
