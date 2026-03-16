// Source: https://leetcode.com/problems/cycle-length-queries-in-a-tree/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n. There is a complete binary tree with 2n - 1 nodes. The root of that tree is the node with the value 1, and every node with a value val in the range [1, 2n - 1 - 1] has two children where:
//
//
// 	The left node has the value 2 * val, and
// 	The right node has the value 2 * val + 1.
//
//
// You are also given a 2D integer array queries of length m, where queries[i] = [ai, bi]. For each query, solve the following problem:
//
//
// 	Add an edge between the nodes with values ai and bi.
// 	Find the length of the cycle in the graph.
// 	Remove the added edge between nodes with values ai and bi.
//
//
// Note that:
//
//
// 	A cycle is a path that starts and ends at the same node, and each edge in the path is visited only once.
// 	The length of a cycle is the number of edges visited in the cycle.
// 	There could be multiple edges between two nodes in the tree after adding the edge of the query.
//
//
// Return an array answer of length m where answer[i] is the answer to the ith query.
//
// Example:
// Input: n = 3, queries = [[5,3],[4,7],[2,3]]
// Output: [4,5,3]
// Explanation: The diagrams above show the tree of 23 - 1 nodes. Nodes colored in red describe the nodes in the cycle after adding the edge.
// - After adding the edge between nodes 3 and 5, the graph contains a cycle of nodes [5,2,1,3]. Thus answer to the first query is 4. We delete the added edge and process the next query.
// - After adding the edge between nodes 4 and 7, the graph contains a cycle of nodes [4,2,1,3,7]. Thus answer to the second query is 5. We delete the added edge and process the next query.
// - After adding the edge between nodes 2 and 3, the graph contains a cycle of nodes [2,1,3]. Thus answer to the third query is 3. We delete the added edge.
//
// Constraints:
// 2 <= n <= 30
// 	m == queries.length
// 	1 <= m <= 105
// 	queries[i].length == 2
// 	1 <= ai, bi <= 2n - 1
// 	ai != bi
//
// Helpful references (internal KB):
// - Lowest Common Ancestor (array, min-window)
//   • When to use: Use when needing to find the lowest common ancestor of two nodes in a tree efficiently for multiple queries. This approach is ideal when the tree is static and preprocessing is acceptable.
//   • Idea: This method finds the LCA by converting the problem into a Range Minimum Query on an Euler tour of the tree's depths. It preprocesses the tree in O(N log N) or O(N) time and answers queries in O(log N) or O(1) time.
//   • Invariants: The Euler tour array correctly records nodes in DFS entry/exit order.; The depth array stores the correct depth for each node in the Euler tour.
//   • Tips: Perform a DFS to construct the Euler tour and depth array.; Store the first occurrence index of each node in the Euler tour.
//   • Pitfalls: Incorrectly constructing the Euler tour or depth array.; Off-by-one errors when mapping Euler tour indices to original nodes.
// - Sqrt Tree (array, tree, recursion, simulation)
//   • When to use: Use for efficient range queries on an array, achieving very low query complexity by leveraging a hierarchical block decomposition and specific structural properties like power-of-two block sizes.
//   • Idea: A Sqrt Tree is a hierarchical data structure designed for answering range queries on an array, achieving O(log log n) or better query time by recursively decomposing the array into blocks and layers.
//   • Invariants: Each layer of the Sqrt Tree consists of segments of equal length.; All blocks within a given layer have an equal, power-of-two size.
//   • Tips: Pad the input array with dummy elements to ensure its size is a power of two for simplified block calculations.; Ensure all block sizes on each layer are powers of two to enable efficient binary representation tricks for queries.
//   • Pitfalls: Incorrectly calculating block boundaries or segment sizes, leading to off-by-one errors or out-of-bounds access.; Overlooking the memory overhead associated with storing precomputed values for all blocks across multiple layers.
// - Linear Diophantine Equation (number, interval, enumeration)
//   • When to use: Use when you need to find or count all integer solutions (x, y) for a linear Diophantine equation ax + by = c, especially when solutions are constrained within specific intervals for x and y.
//   • Idea: This method finds all integer solutions to a linear Diophantine equation ax + by = c within given x and y intervals. It first finds a particular solution, then uses properties of the general solution to determine the valid range for x, and enumerates solutions in O(N) time where N is the number of solutions.
//   • Invariants: The current (x, y) pair always satisfies the linear Diophantine equation ax + by = c.; The current x value is an integer and satisfies the effective bounds l_x <= x <= r_x.
//   • Tips: Pre-divide coefficients a, b, c by gcd(a, b) to simplify the equation.; Use the Extended Euclidean Algorithm to find an initial particular solution (x0, y0).
//   • Pitfalls: Failing to check if c is divisible by gcd(a, b) before proceeding, leading to incorrect results.; Incorrectly applying the shifting logic for x and y bounds, resulting in an invalid solution range.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* cycleLengthQueries(int n, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int *results = (int*)malloc(queriesSize * sizeof(int));
    if (!results) return NULL;

    for (int i = 0; i < queriesSize; ++i) {
        int a = queries[i][0];
        int b = queries[i][1];
        int length = 0;

        /* Move up the tree until both nodes are the same */
        while (a != b) {
            if (a > b) {
                a /= 2;
            } else {
                b /= 2;
            }
            length++;
        }
        /* The cycle length is twice the path length between a and b */
        results[i] = length * 2;
    }

    *returnSize = queriesSize;
    return results;     
}
