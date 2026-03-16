// Source: https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, the depth of each node is the shortest distance to the root.
//
// Return the smallest subtree such that it contains all the deepest nodes in the original tree.
//
// A node is called the deepest if it has the largest depth possible among any node in the entire tree.
//
// The subtree of a node is a tree consisting of that node, plus the set of all descendants of that node.
//
// Example:
// Input: root = [3,5,1,6,2,0,8,null,null,7,4]
// Output: [2,7,4]
// Explanation: We return the node with value 2, colored in yellow in the diagram.
// The nodes coloured in blue are the deepest nodes of the tree.
// Notice that nodes 5, 3 and 2 contain the deepest nodes in the tree but node 2 is the smallest subtree among them, so we return it.
//
// Constraints:
// The number of nodes in the tree will be in the range [1, 500].
// 	0 <= Node.val <= 500
// 	The values of the nodes in the tree are unique.
//
//
//  
// Note: This question is the same as 1123: https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/
//
// Helpful references (internal KB):
// - Lowest Common Ancestor (array, min-window)
//   • When to use: Use when needing to find the lowest common ancestor of two nodes in a tree efficiently for multiple queries. This approach is ideal when the tree is static and preprocessing is acceptable.
//   • Idea: This method finds the LCA by converting the problem into a Range Minimum Query on an Euler tour of the tree's depths. It preprocesses the tree in O(N log N) or O(N) time and answers queries in O(log N) or O(1) time.
//   • Invariants: The Euler tour array correctly records nodes in DFS entry/exit order.; The depth array stores the correct depth for each node in the Euler tour.
//   • Tips: Perform a DFS to construct the Euler tour and depth array.; Store the first occurrence index of each node in the Euler tour.
//   • Pitfalls: Incorrectly constructing the Euler tour or depth array.; Off-by-one errors when mapping Euler tour indices to original nodes.
// - Lowest Common Ancestor - Binary Lifting (tree, array, binary-lifting, dfs)
//   • When to use: Use binary lifting when you need to answer multiple Lowest Common Ancestor (LCA) queries or ancestor relationship checks efficiently on a static tree.
//   • Idea: Binary lifting precomputes ancestor pointers using DFS to answer Lowest Common Ancestor (LCA) queries and ancestor checks in O(log N) time per query, after O(N log N) preprocessing.
//   • Invariants: For any node `u` and power `k`, `up[u][k]` is the 2^k-th ancestor of `u`.; `depth[u]` correctly represents the distance from the root to node `u`.
//   • Tips: Precompute `up[u][k]` as the 2^k-th ancestor of `u`.; Use DFS to fill the `up` array and node depths.
//   • Pitfalls: Incorrectly calculating `log N` for array dimensions.; Failing to handle the root node's ancestors (e.g., `up[root][k]` should be itself or an invalid node).
// - Lowest Common Ancestor - Farach-Colton and Bender Algorithm (tree, array, dfs)
//   • When to use: When frequent LCA queries are needed on a static tree, and optimal query time is critical. It's suitable for scenarios requiring O(1) query time after initial preprocessing.
//   • Idea: This algorithm finds the Lowest Common Ancestor (LCA) of two nodes in a tree by reducing the problem to Range Minimum Query (RMQ) on an Euler tour. It preprocesses the tree in O(N) time using DFS to build an array of nodes and their depths, then answers LCA queries in O(1) time.
//   • Invariants: The Euler tour array contains every edge traversed twice, and each node appears at least once.; The depth array stores the correct distance from the root for each node's occurrence in the Euler tour.
//   • Tips: Perform a DFS to construct the Euler tour and depth array.; Store both the node identifier and its depth during the Euler tour.
//   • Pitfalls: Incorrectly defining the start and end indices for the RMQ on the Euler tour.; Off-by-one errors when mapping Euler tour indices to original nodes or depths.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* subtreeWithAllDeepest(struct TreeNode* root) {
    if (!root) {
        return NULL;
    }
    
    struct TreeNode* left = subtreeWithAllDeepest(root->left);
    struct TreeNode* right = subtreeWithAllDeepest(root->right);
    
    if (!left) {
        return right;
    }
    
    if (!right) {
        return left;
    }
    
    return root;        
}
