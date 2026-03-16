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
// - Topological Sorting (graph, array, dfs, topo)
//   • When to use: Use for graph or tree traversal, pathfinding, cycle detection, or topological sorting in DAGs. It's also suitable for exploring all states in a search space.
//   • Idea: DFS explores as far as possible along each branch before backtracking, typically using recursion or an explicit stack. Topological sort orders nodes in a DAG such that for every directed edge u -> v, u comes before v, achievable with DFS in O(V+E) time.
//   • Invariants: All nodes reachable from the current path have been explored or are in the recursion stack.; A node is marked 'visited' only after all its descendants have been fully explored.
//   • Tips: Use a visited set/array to prevent infinite loops in graphs and redundant computations.; Recursion is natural for DFS, but an explicit stack can avoid recursion depth limits.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect results.; Exceeding recursion depth limits for very deep graphs or trees.
// - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
//   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
//   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
//   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
//   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
//   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
// - Backtracking Algorithm (graph, backtracking, recursion, dfs)
//   • When to use: Used when exploring multiple possibilities to find a solution incrementally, often involving undoing choices if they lead to a dead end.
//   • Idea: Backtracking is a problem-solving technique that incrementally builds a solution by trying options and undoing them upon reaching a dead end. It typically explores a search space in a depth-first manner, often resulting in exponential time complexity.
//   • Invariants: The current partial solution is valid up to the current decision point.; All choices made to reach the current state can be systematically undone.
//   • Tips: Define clear base cases for recursive termination.; Identify decision points and available choices at each step.
//   • Pitfalls: Forgetting to undo changes (backtrack) after exploring a path.; Incorrectly defining base cases, leading to infinite recursion or wrong results.
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
    // Helper function to perform DFS and backtracking
    void dfs(int node, int target, int* path, int pathSize, int** graph, int* graphColSize, int*** result, int* returnSize, int** returnColumnSizes) {
        // Add the current node to the path
        path[pathSize++] = node;

        // If we reached the target node, add the path to the result
        if (node == target) {
            (*returnSize)++;
            *result = realloc(*result, (*returnSize) * sizeof(int*));
            (*result)[(*returnSize) - 1] = malloc(pathSize * sizeof(int));
            memcpy((*result)[(*returnSize) - 1], path, pathSize * sizeof(int));
            (*returnColumnSizes)[(*returnSize) - 1] = pathSize;
        } else {
            // Explore neighbors
            for (int i = 0; i < graphColSize[node]; i++) {
                dfs(graph[node][i], target, path, pathSize, graph, graphColSize, result, returnSize, returnColumnSizes);
            }
        }

        // Backtrack: remove the current node from the path
        pathSize--;
    }

    // Initialize variables
    int** result = NULL;
    *returnSize = 0;
    *returnColumnSizes = malloc(graphSize * sizeof(int*));
    int* path = malloc(graphSize * sizeof(int));

    // Start DFS from node 0 to node n-1
    dfs(0, graphSize - 1, path, 0, graph, graphColSize, &result, returnSize, returnColumnSizes);

    // Clean up
    free(path);
    return result;      
}
