// Source: https://leetcode.com/problems/maximum-width-of-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the maximum width of the given tree.
//
// The maximum width of a tree is the maximum width among all levels.
//
// The width of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes), where the null nodes between the end-nodes that would be present in a complete binary tree extending down to that level are also counted into the length calculation.
//
// It is guaranteed that the answer will in the range of a 32-bit signed integer.
//
// Example:
// Input: root = [1,3,2,5,3,null,9]
// Output: 4
// Explanation: The maximum width exists in the third level with length 4 (5,3,null,9).
//
// Constraints:
// The number of nodes in the tree is in the range [1, 3000].
// 	-100 <= Node.val <= 100
//
// Helpful references (internal KB):
// - Breadth-first search (graph, array, bfs, counting)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level to explore all reachable nodes. It is also suitable for finding connected components or checking reachability.
//   • Idea: Breadth-first search explores a graph layer by layer, finding the shortest path in terms of edges from a source node to all other reachable nodes. It typically runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently in the queue are at the same or next level of traversal from the source.; All nodes already dequeued have been fully processed, and their unvisited neighbors have been enqueued.
//   • Tips: Use a queue to manage nodes to visit in a FIFO manner.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing and cycles.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect path lengths.; Not handling disconnected components if the goal is to traverse the entire graph.
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
//   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
//   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
//   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
//   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
//   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
// - Balanced Search Trees (tree, ds, binary-search, recursion)
//   • When to use: When you need to store a dynamic set of ordered data and require guaranteed logarithmic time complexity for search, insertion, and deletion operations, even in worst-case scenarios.
//   • Idea: Balanced search trees are a class of self-balancing binary search trees that maintain a logarithmic height to ensure O(log N) time complexity for core operations like search, insertion, and deletion. They achieve this balance through structural modifications such as rotations or node splitting/merging.
//   • Invariants: For any node, all keys in its left subtree are less than its key(s), and all keys in its right subtree are greater than its key(s).; The height of the tree is always proportional to log N, ensuring O(log N) operations.
//   • Tips: Understand the specific balancing rules (e.g., AVL rotations, Red-Black tree color properties, 2-3 tree node splits).; Consider the trade-offs between different balanced tree types (e.g., simpler implementation vs. stricter balance).
//   • Pitfalls: Implementation complexity can be high due to intricate rebalancing logic.; Overhead for rebalancing operations might be noticeable for very small N.
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
int widthOfBinaryTree(struct TreeNode* root) {
    if (!root) return 0;

    // Queue for BFS: each element is a pair (node, index)
    struct TreeNode** queue = (struct TreeNode**)malloc(3000 * sizeof(struct TreeNode*));
    unsigned long long* indices = (unsigned long long*)malloc(3000 * sizeof(unsigned long long));
    int front = 0, back = 0;

    queue[back] = root;
    indices[back] = 0;
    back++;

    unsigned long long maxWidth = 1;

    while (front < back) {
        int levelSize = back - front;
        unsigned long long levelStartIndex = indices[front];
        unsigned long long levelEndIndex = indices[back - 1];

        // Update max width
        unsigned long long currentWidth = levelEndIndex - levelStartIndex + 1;
        if (currentWidth > maxWidth) {
            maxWidth = currentWidth;
        }

        // Process the current level
        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = queue[front];
            unsigned long long index = indices[front];
            front++;

            if (node->left) {
                queue[back] = node->left;
                indices[back] = 2 * index + 1;
                back++;
            }
            if (node->right) {
                queue[back] = node->right;
                indices[back] = 2 * index + 2;
                back++;
            }
        }
    }

    free(queue);
    free(indices);

    return (int)maxWidth;       
}
