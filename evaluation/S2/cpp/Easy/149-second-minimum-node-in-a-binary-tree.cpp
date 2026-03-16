// Source: https://leetcode.com/problems/second-minimum-node-in-a-binary-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given a non-empty special binary tree consisting of nodes with the non-negative value, where each node in this tree has exactly two or zero sub-node. If the node has two sub-nodes, then this node's value is the smaller value among its two sub-nodes. More formally, the property root.val = min(root.left.val, root.right.val) always holds.
//
// Given such a binary tree, you need to output the second minimum value in the set made of all the nodes' value in the whole tree.
//
// If no such second minimum value exists, output -1 instead.
//
// Example:
// Input: root = [2,2,5,null,null,5,7]
// Output: 5
// Explanation: The smallest value is 2, the second smallest value is 5.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 25].
// 	1 <= Node.val <= 231 - 1
// 	root.val == min(root.left.val, root.right.val) for each internal node of the tree.
//
// Helpful references (internal KB):
// - Second Best Minimum Spanning Tree (graph, tree, mst-kruskal, lca, binary-lifting, enumeration)
//   • When to use: When you need to find a spanning tree with the second smallest total edge weight, typically after finding the primary Minimum Spanning Tree.
//   • Idea: This algorithm finds the second best Minimum Spanning Tree by iterating through non-MST edges, adding each to the MST to form a cycle, and then removing the maximum weight edge on that cycle (excluding the added edge). It leverages Kruskal's for the initial MST and LCA with binary lifting for efficient path maximum queries, achieving an overall time complexity of O(E log E + E log V).
//   • Invariants: The initial MST is always a valid spanning tree with minimum total weight.; For any non-MST edge (u, v) added, a unique cycle is formed in the current graph.
//   • Tips: Precompute LCA and maximum edge weights on paths using binary lifting for efficiency.; The initial MST can be found using Kruskal's or Prim's algorithm.
//   • Pitfalls: Incorrectly identifying the maximum weight edge on the cycle when adding a non-MST edge.; Forgetting to exclude the newly added edge itself when finding the maximum edge on the cycle.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Range Minimum Query (array, tree, divide-and-conquer)
//   • When to use: When needing to find the minimum (or maximum) value within various specified ranges of an array efficiently. Suitable for scenarios with many queries on a fixed or frequently updated dataset.
//   • Idea: This technique precomputes answers for subproblems, typically by building a tree-like structure or a table, to efficiently answer queries for the minimum (or maximum) value within a given range. It achieves O(log N) or O(1) query time after O(N log N) or O(N) preprocessing, depending on the specific data structure used.
//   • Invariants: For a Segment Tree node covering range [L, R], its value stores the minimum of all elements in the original array from index L to R.; For any query range [Q_L, Q_R], the combined result from relevant tree nodes correctly represents the minimum in [Q_L, Q_R].
//   • Tips: For static arrays, Sparse Table offers O(1) query time after O(N log N) preprocessing.; For dynamic arrays with updates, Segment Tree offers O(log N) query and update time after O(N) preprocessing.
//   • Pitfalls: Off-by-one errors when defining range boundaries or calculating indices.; Incorrect merge logic for segment tree nodes (e.g., using sum instead of min).
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
    int findSecondMinimumValue(TreeNode* root) {
        if (!root) return -1;
        int minVal = root->val;
        int secondMin = -1;
        
        // Helper function to traverse the tree
        function<void(TreeNode*)> dfs = [&](TreeNode* node) {
            if (!node) return;
            if (node->val > minVal) {
                if (secondMin == -1 || node->val < secondMin) {
                    secondMin = node->val;
                }
            } else if (node->val == minVal) {
                dfs(node->left);
                dfs(node->right);
            }
        };
        
        dfs(root);
        return secondMin;               
    }
};
