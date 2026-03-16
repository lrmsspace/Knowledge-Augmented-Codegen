// Source: https://leetcode.com/problems/count-complete-tree-nodes/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a complete binary tree, return the number of the nodes in the tree.
//
// According to Wikipedia, every level, except possibly the last, is completely filled in a complete binary tree, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.
//
// Design an algorithm that runs in less than O(n) time complexity.
//
// Example:
// Input: root = [1,2,3,4,5,6]
// Output: 6
//
// Constraints:
// The number of nodes in the tree is in the range [0, 5 * 104].
// 	0 <= Node.val <= 5 * 104
// 	The tree is guaranteed to be complete.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Breadth-first search (graph, array, bfs, counting)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level to explore all reachable nodes. It is also suitable for finding connected components or checking reachability.
//   • Idea: Breadth-first search explores a graph layer by layer, finding the shortest path in terms of edges from a source node to all other reachable nodes. It typically runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently in the queue are at the same or next level of traversal from the source.; All nodes already dequeued have been fully processed, and their unvisited neighbors have been enqueued.
//   • Tips: Use a queue to manage nodes to visit in a FIFO manner.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing and cycles.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect path lengths.; Not handling disconnected components if the goal is to traverse the entire graph.
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
int countNodes(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    int left_depth = 0, right_depth = 0;
    struct TreeNode* left_node = root;
    struct TreeNode* right_node = root;

    while (left_node != NULL) {
        left_depth++;
        left_node = left_node->left;
    }

    while (right_node != NULL) {
        right_depth++;
        right_node = right_node->right;
    }

    if (left_depth == right_depth) {
        return (1 << left_depth) - 1; // 2^depth - 1
    }

    return 1 + countNodes(root->left) + countNodes(root->right);        
}
