// Source: https://leetcode.com/problems/cousins-in-binary-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary tree with unique values and the values of two different nodes of the tree x and y, return true if the nodes corresponding to the values x and y in the tree are cousins, or false otherwise.
//
// Two nodes of a binary tree are cousins if they have the same depth with different parents.
//
// Note that in a binary tree, the root node is at the depth 0, and children of each depth k node are at the depth k + 1.
//
// Example:
// Input: root = [1,2,3,4], x = 4, y = 3
// Output: false
//
// Constraints:
// The number of nodes in the tree is in the range [2, 100].
// 	1 <= Node.val <= 100
// 	Each node has a unique value.
// 	x != y
// 	x and y are exist in the tree.
//
// Helpful references (internal KB):
// - Lowest Common Ancestor - Binary Lifting (tree, array, dfs, binary-lifting)
//   • When to use: When you need to find the lowest common ancestor of multiple pairs of nodes in a static tree efficiently. It's suitable for scenarios requiring fast query times after initial preprocessing.
//   • Idea: Binary lifting precomputes ancestors at powers of two distances for each node, enabling O(log N) LCA queries after O(N log N) preprocessing. It finds the LCA by lifting nodes to the same depth and then simultaneously upwards.
//   • Invariants: `up[u][j]` stores the `2^j`-th ancestor of node `u`.; For any node `u`, `depth[u]` is its distance from the root.
//   • Tips: Precompute depths of all nodes using DFS from the root.; Initialize `up[u][0]` as the direct parent of `u` for all nodes.
//   • Pitfalls: Incorrectly handling the root's parent or depth calculation.; Off-by-one errors in `logN` calculation for array dimensions.
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
// - Depth First Search (graph, dfs)
//   • When to use: Use DFS to explore all reachable vertices from a source, find connected components, or detect cycles in a graph. It is suitable for problems requiring deep exploration before backtracking.
//   • Idea: Depth First Search systematically explores a graph by going as deep as possible along each branch before backtracking. It visits each vertex and edge at most once, resulting in an O(V + E) time complexity.
//   • Invariants: Before visiting a node 'u', it is marked as unvisited.; After visiting a node 'u', it is marked as visited, and all its reachable neighbors have been explored.
//   • Tips: Use a 'visited' set or array to prevent infinite loops in cyclic graphs.; Recursion is common, but an explicit stack can manage deep graphs or avoid recursion limits.
//   • Pitfalls: Can lead to stack overflow errors on very deep graphs if implemented recursively.; Does not guarantee shortest paths in general unweighted graphs (BFS does).
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
bool isCousins(struct TreeNode* root, int x, int y) {
    if (!root) return false;

    struct TreeNode* queue[100];
    int front = 0, back = 0;
    queue[back++] = root;

    while (front < back) {
        int size = back - front;
        bool x_found = false, y_found = false;

        for (int i = 0; i < size; i++) {
            struct TreeNode* node = queue[front++];

            if (node->left && node->right) {
                if ((node->left->val == x && node->right->val == y) ||
                    (node->left->val == y && node->right->val == x)) {
                    return false; // same parent
                }
            }

            if (node->left) {
                if (node->left->val == x) x_found = true;
                if (node->left->val == y) y_found = true;
                queue[back++] = node->left;
            }

            if (node->right) {
                if (node->right->val == x) x_found = true;
                if (node->right->val == y) y_found = true;
                queue[back++] = node->right;
            }
        }

        if (x_found && y_found) return true; // found both at the same level
        if (x_found || y_found) return false; // found only one at this level
    }

    return false; // not found      
}
