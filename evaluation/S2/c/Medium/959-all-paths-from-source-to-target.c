// Source: https://leetcode.com/problems/all-paths-from-source-to-target/   |   Difficulty: Medium
//
// Problem Description:
// Given a directed acyclic graph (DAG) of n nodes labeled from 0 to n - 1, find all possible paths from node 0 to node n - 1 and return them in any order.
//
// The graph is given as follows: graph[i] is a list of all nodes you can visit from node i (i.e., there is a directed edge from node i to node graph[i][j]).
//
// Example:
// Input: graph = [[1,2],[3],[3],[]]
// Output: [[0,1,3],[0,2,3]]
// Explanation: There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.
//
// Constraints:
// n == graph.length
// 	2 <= n <= 15
// 	0 <= graph[i][j] < n
// 	graph[i][j] != i (i.e., there will be no self-loops).
// 	All the elements of graph[i] are unique.
// 	The input graph is guaranteed to be a DAG.
//
// Helpful references (internal KB):
// - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
//   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
//   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
//   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
//   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
//   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** allPathsSourceTarget(int** graph, int graphSize, int* graphColSize, int* returnSize, int** returnColumnSizes) {
    // This problem can be solved using Depth-First Search (DFS) to explore all possible paths from the source node (0) to the target node (n - 1). We will use a recursive helper function to perform the DFS and store the paths in a dynamic array.

    // Define a structure to hold the paths and their sizes
    typedef struct {
        int** paths;          // Array of paths
        int* pathSizes;       // Sizes of each path
        int count;            // Number of paths found
        int capacity;         // Capacity of the paths array
    } PathList;

    // Initialize the PathList structure
    PathList pathList;
    pathList.count = 0;
    pathList.capacity = 10; // Initial capacity for storing paths
    pathList.paths = (int**)malloc(pathList.capacity * sizeof(int*));
    pathList.pathSizes = (int*)malloc(pathList.capacity * sizeof(int));

    // Helper function for DFS
    void dfs(int node, int* currentPath, int currentSize) {
        // Add the current node to the path
        currentPath[currentSize] = node;
        currentSize++;

        // If we reached the target node, save the path
        if (node == graphSize - 1) {
            if (pathList.count == pathList.capacity) {
                // Resize the paths array if needed
                pathList.capacity *= 2;
                pathList.paths = (int**)realloc(pathList.paths, pathList.capacity * sizeof(int*));
                pathList.pathSizes = (int*)realloc(pathList.pathSizes, pathList.capacity * sizeof(int));
            }
            // Save the current path
            pathList.paths[pathList.count] = (int*)malloc(currentSize * sizeof(int));
            memcpy(pathList.paths[pathList.count], currentPath, currentSize * sizeof(int));
            pathList.pathSizes[pathList.count] = currentSize;
            pathList.count++;
        } else {
            // Continue DFS for each neighbor of the current node
            for (int i = 0; i < graphColSize[node]; i++) {
                dfs(graph[node][i], currentPath, currentSize);
            }
        }
    }

    // Start DFS from the source node (0)
    int* currentPath = (int*)malloc(graphSize * sizeof(int)); // Temporary array to hold the current path
    dfs(0, currentPath, 0);
    *returnSize = pathList.count;
    *returnColumnSizes = pathList.pathSizes;
    free(currentPath);
    return pathList.paths;
}
