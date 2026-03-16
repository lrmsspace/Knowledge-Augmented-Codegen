// Source: https://leetcode.com/problems/find-eventual-safe-states/   |   Difficulty: Medium
//
// Problem Description:
// There is a directed graph of n nodes with each node labeled from 0 to n - 1. The graph is represented by a 0-indexed 2D integer array graph where graph[i] is an integer array of nodes adjacent to node i, meaning there is an edge from node i to each node in graph[i].
//
// A node is a terminal node if there are no outgoing edges. A node is a safe node if every possible path starting from that node leads to a terminal node (or another safe node).
//
// Return an array containing all the safe nodes of the graph. The answer should be sorted in ascending order.
//
// Example:
// Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
// Output: [2,4,5,6]
// Explanation: The given graph is shown above.
// Nodes 5 and 6 are terminal nodes as there are no outgoing edges from either of them.
// Every path starting at nodes 2, 4, 5, and 6 all lead to either node 5 or 6.
//
// Constraints:
// n == graph.length
// 	1 <= n <= 104
// 	0 <= graph[i].length <= n
// 	0 <= graph[i][j] <= n - 1
// 	graph[i] is sorted in a strictly increasing order.
// 	The graph may contain self-loops.
// 	The number of edges in the graph will be in the range [1, 4 * 104].
//
// Helpful references (internal KB):
// - Depth-first search (graph, array, dfs)
//   • When to use: Use when exploring all reachable nodes from a starting point, detecting cycles, or performing a topological sort on a graph. It's suitable for problems requiring deep exploration before backtracking.
//   • Idea: Depth-first search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically runs in O(V + E) time for graphs and O(V) for trees.
//   • Invariants: For any visited node 'u', 'marked[u]' is true.; If a path exists from source 's' to 'v', then DFS from 's' will eventually mark 'v'.
//   • Tips: Use a 'visited' array or set to prevent infinite loops in cyclic graphs.; Maintain a 'parent' or 'edgeTo' array for path reconstruction or cycle detection.
//   • Pitfalls: Stack overflow with deep recursion on large graphs.; Incorrectly handling cycles in undirected graphs without parent tracking.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
// - Mergesort (array, merge-sort, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, especially for large datasets or external sorting where data might not fit in memory.
//   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and requires O(N) auxiliary space.
//   • Invariants: The elements `index[lo...k-1]` are sorted and contain the smallest `k-lo` elements from the original `aux[lo...mid]` and `aux[mid+1...hi]` segments.; Pointer `i` always indicates the next element to consider from the left sorted sub-array (`aux[lo...mid]`).
//   • Tips: Implement the merge step carefully to ensure stability.; Consider an iterative bottom-up approach to avoid recursion overhead.
//   • Pitfalls: High auxiliary space complexity (O(N)) can be a concern for memory-constrained systems.; Recursive calls can lead to stack overflow for very large inputs without tail call optimization.
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
int* eventualSafeNodes(int** graph, int graphSize, int* graphColSize, int* returnSize) {
    enum { UNVISITED, VISITING, SAFE, UNSAFE };
    int* state = (int*)calloc(graphSize, sizeof(int));
    int* result = (int*)malloc(graphSize * sizeof(int));
    int resCount = 0;

    int dfs(int node) {
        if (state[node] == VISITING) {
            state[node] = UNSAFE;
            return 0;
        }
        if (state[node] == SAFE) {
            return 1;
        }
        if (state[node] == UNSAFE) {
            return 0;
        }

        state[node] = VISITING;
        for (int i = 0; i < graphColSize[node]; i++) {
            int neighbor = graph[node][i];
            if (!dfs(neighbor)) {
                state[node] = UNSAFE;
                return 0;
            }
        }
        state[node] = SAFE;
        return 1;
    }

    for (int i = 0; i < graphSize; i++) {
        if (dfs(i)) {
            result[resCount++] = i;
        }
    }

    free(state);
    *returnSize = resCount;
    return result;      
}
