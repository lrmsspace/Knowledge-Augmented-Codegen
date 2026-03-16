// Source: https://leetcode.com/problems/n-ary-tree-level-order-traversal/   |   Difficulty: Medium
//
// Problem Description:
// Given an n-ary tree, return the level order traversal of its nodes' values.
//
// Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See examples).
//
// Example:
// Input: root = [1,null,3,2,4,null,5,6]
// Output: [[1],[3,2,4],[5,6]]
//
// Constraints:
// The height of the n-ary tree is less than or equal to 1000
// 	The total number of nodes is between [0, 104]
//
// Helpful references (internal KB):
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when you need to find the shortest path (in terms of number of edges) from a source node to all other reachable nodes in an unweighted graph. It is also suitable for exploring a graph layer by layer.
//   • Idea: BFS systematically explores a graph level by level, starting from a source node, ensuring all nodes at a given distance are visited before moving to the next distance level. It operates in O(N + M) time for N vertices and M edges.
//   • Invariants: All nodes currently in the queue are at the same or adjacent distance level from the source.; The 'used' array accurately reflects all nodes that have been added to the queue for processing.
//   • Tips: Always use a queue to maintain the order of nodes to visit.; Utilize a 'visited' array or set to prevent revisiting nodes and infinite loops.
//   • Pitfalls: Does not find shortest paths in weighted graphs unless weights are 0 or 1 (use Dijkstra for general weighted graphs).; Forgetting to mark nodes as visited can lead to incorrect results or TLE.
// - Sqrt Tree (array, number, bitmask-dp, enumeration)
//   • When to use: Used for answering range queries on a static array by recursively decomposing it into square root sized blocks, achieving O(log log N) query time.
//   • Idea: A Sqrt Tree is a recursive data structure that decomposes an array into blocks of square root size, building a similar structure on each block. It allows for efficient range queries, typically achieving O(log log N) query time after an O(N log log N) precomputation.
//   • Invariants: Each node in the Sqrt Tree represents a contiguous segment of the original array.; A node representing a segment of length k has sqrt(k) children, each covering a block of sqrt(k) elements.
//   • Tips: Precompute answers for all possible block combinations within a node.; Handle queries spanning multiple blocks by combining precomputed prefix, suffix, and full block results.
//   • Pitfalls: High constant factors due to complex precomputation per node.; Memory usage can be significant, O(N log log N), for large N.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numChildren;
 *     struct Node** children;
 * };
 */

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct Node* root, int* returnSize, int** returnColumnSizes) {
    if (root == NULL) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    // We will use a queue to perform BFS
    struct Node** queue = (struct Node**)malloc(sizeof(struct Node*) * 10000); // Assuming max nodes is 10000
    int front = 0, rear = 0;

    // Enqueue the root node
    queue[rear++] = root;

    // Prepare the result array and column sizes array
    int** result = (int**)malloc(sizeof(int*) * 1000); // Assuming max levels is 1000
    int* columnSizes = (int*)malloc(sizeof(int) * 1000);
    int levelCount = 0;

    while (front < rear) {
        int levelSize = rear - front; // Number of nodes at the current level
        columnSizes[levelCount] = levelSize; // Store the number of nodes at this level

        // Allocate space for the current level's values
        result[levelCount] = (int*)malloc(sizeof(int) * levelSize);

        for (int i = 0; i < levelSize; i++) {
            struct Node* currentNode = queue[front++]; // Dequeue a node

            // Store its value in the result array
            result[levelCount][i] = currentNode->val;

            // Enqueue its children
            for (int j = 0; j < currentNode->numChildren; j++) {
                queue[rear++] = currentNode->children[j];
            }
        }
        levelCount++; // Move to the next level
    }

    free(queue); // Free the queue memory

    *returnSize = levelCount; // Set the return size to the number of levels
    *returnColumnSizes = columnSizes; // Set the return column sizes

    return result; // Return the result array       
}
