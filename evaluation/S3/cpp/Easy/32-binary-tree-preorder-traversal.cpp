// Source: https://leetcode.com/problems/binary-tree-preorder-traversal/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary tree, return the preorder traversal of its nodes' values.
//
// Example:
// Input: root = [1,null,2,3]
//
// Output: [1,2,3]
//
// Explanation:
//
// Constraints:
// The number of nodes in the tree is in the range [0, 100].
// 	-100 <= Node.val <= 100
//
//
//  
// Follow up: Recursive solution is trivial, could you do it iteratively?
//
// Helpful references (internal KB):
// - Prüfer code (tree, heap, simulation, greedy)
//   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
//   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
//   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
//   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
//   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
// - Prüfer code (tree, heap, simulation, greedy)
//   • When to use: Use when counting labeled trees or converting between a labeled tree and a unique sequence representation for combinatorial analysis. It provides a bijection for problems involving N labeled nodes.
//   • Idea: Prüfer code is a unique sequence of length N-2 that represents a labeled tree with N nodes. It is constructed by iteratively removing the smallest-labeled leaf and recording its neighbor, and can be reconstructed back into the tree.
//   • Invariants: The Prüfer sequence always contains N-2 elements for a tree with N nodes.; At each step of encoding, the removed node is a leaf with the smallest label among all current leaves.
//   • Tips: Maintain an array of node degrees for efficient updates.; Use a min-priority queue to quickly find the smallest-labeled leaf.
//   • Pitfalls: Incorrectly updating node degrees after removal.; Off-by-one errors when dealing with 0-indexed vs. 1-indexed labels.
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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }
        
        stack<TreeNode*> nodeStack;
        nodeStack.push(root);
        
        while (!nodeStack.empty()) {
            TreeNode* currentNode = nodeStack.top();
            nodeStack.pop();
            result.push_back(currentNode->val);
            
            // Push right child first so that left child is processed first
            if (currentNode->right != nullptr) {
                nodeStack.push(currentNode->right);
            }
            if (currentNode->left != nullptr) {
                nodeStack.push(currentNode->left);
            }
        }
        
        return result;          
    }
};
