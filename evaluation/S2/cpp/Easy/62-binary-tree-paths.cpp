// Source: https://leetcode.com/problems/binary-tree-paths/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary tree, return all root-to-leaf paths in any order.
//
// A leaf is a node with no children.
//
// Example:
// Input: root = [1,2,3,null,5]
// Output: ["1->2->5","1->3"]
//
// Constraints:
// The number of nodes in the tree is in the range [1, 100].
// 	-100 <= Node.val <= 100
//
// Helpful references (internal KB):
// - Prüfer code (tree, heap, simulation, greedy)
//   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
//   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
//   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
//   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
//   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
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
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> paths;
        if (!root) return paths; // Return empty if root is null

        // Helper function to perform DFS and build paths
        function<void(TreeNode*, string)> dfs = [&](TreeNode* node, string path) {
            if (!node) return; // Base case: null node

            // Append current node's value to the path
            path += to_string(node->val);

            // If it's a leaf node, add the path to the result
            if (!node->left && !node->right) {
                paths.push_back(path);
                return;
            }

            // Continue DFS on left and right children
            dfs(node->left, path + "->");
            dfs(node->right, path + "->");
        };

        dfs(root, ""); // Start DFS with an empty path
        return paths;           
    }
};
