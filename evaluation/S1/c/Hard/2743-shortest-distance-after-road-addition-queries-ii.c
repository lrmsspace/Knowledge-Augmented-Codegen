// Source: https://leetcode.com/problems/shortest-distance-after-road-addition-queries-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and a 2D integer array queries.
//
// There are n cities numbered from 0 to n - 1. Initially, there is a unidirectional road from city i to city i + 1 for all 0 <= i < n - 1.
//
// queries[i] = [ui, vi] represents the addition of a new unidirectional road from city ui to city vi. After each query, you need to find the length of the shortest path from city 0 to city n - 1.
//
// There are no two queries such that queries[i][0] < queries[j][0] < queries[i][1] < queries[j][1].
//
// Return an array answer where for each i in the range [0, queries.length - 1], answer[i] is the length of the shortest path from city 0 to city n - 1 after processing the first i + 1 queries.
//
// Example:
// Input: n = 5, queries = [[2,4],[0,2],[0,4]]
//
// Output: [3,2,1]
//
// Explanation: 
//
//
//
// After the addition of the road from 2 to 4, the length of the shortest path from 0 to 4 is 3.
//
//
//
// After the addition of the road from 0 to 2, the length of the shortest path from 0 to 4 is 2.
//
//
//
// After the addition of the road from 0 to 4, the length of the shortest path from 0 to 4 is 1.
//
// Constraints:
// 3 <= n <= 105
// 	1 <= queries.length <= 105
// 	queries[i].length == 2
// 	0 <= queries[i][0] < queries[i][1] < n
// 	1 < queries[i][1] - queries[i][0]
// 	There are no repeated roads among the queries.
// 	There are no two queries such that i != j and queries[i][0] < queries[j][0] < queries[i][1] < queries[j][1].
//
// Helpful references (internal KB):
// - Range Minimum Query (array, tree, segment-tree)
//   • When to use: Use when needing to efficiently query minimums over arbitrary ranges and perform point or range updates on an array.
//   • Idea: A segment tree is a tree data structure used for storing information about intervals or segments. It allows answering range queries and performing updates in logarithmic time, typically O(log N) for both.
//   • Invariants: Each node in the segment tree represents a contiguous subsegment of the original array.; A parent node's value is derived from its children's values (e.g., minimum of children).
//   • Tips: Build the tree recursively, dividing the array into halves until leaf nodes are reached.; Query operations involve traversing relevant segments, combining results from child nodes.
//   • Pitfalls: Incorrectly handling array indexing (0-based vs. 1-based) can lead to off-by-one errors.; Forgetting to update parent nodes after a child's value changes during an update operation.
// - Dijkstra Algorithm (graph, array, dijkstra, greedy)
//   • When to use: Use this algorithm to find the shortest paths from a single source to all other vertices in a graph. It is applicable when all edge weights are non-negative.
//   • Idea: Dijkstra's algorithm finds the shortest paths from a single source vertex to all other vertices in a weighted graph with non-negative edge weights. It iteratively selects the unvisited vertex with the smallest known distance, relaxing its outgoing edges, achieving O(V^2 + E) or O(E log V) complexity.
//   • Invariants: For any marked vertex v, d[v] holds the true shortest path distance from s to v.; For any unmarked vertex v, d[v] holds the shortest path distance from s to v using only marked intermediate vertices.
//   • Tips: Use a priority queue for sparse graphs to optimize performance to O(E log V).; Initialize distances to infinity for all vertices except the source, which is zero.
//   • Pitfalls: Dijkstra's algorithm does not work correctly with negative edge weights; use Bellman-Ford or SPFA instead.; Failing to use an efficient data structure (like a priority queue) for vertex selection can lead to O(V^2) performance on sparse graphs.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
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
int* shortestDistanceAfterQueries(int n, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int* result = (int*)malloc(queriesSize * sizeof(int));
    int left = 0, right = n - 1;
    for (int i = 0; i < queriesSize; ++i) {
        int u = queries[i][0];
        int v = queries[i][1];
        if (u <= left && v >= right) {
            result[i] = 1;
            left = right; // shortest path is now direct
        } else if (u <= left && v < right && v > left) {
            result[i] = 2 + (right - v);
            left = v; // update left boundary
        } else if (u > left && v >= right && u < right) {
            result[i] = 2 + (u - left);
            right = u; // update right boundary
        } else {
            result[i] = right - left; // no improvement
        }
    }
    *returnSize = queriesSize;
    return result;      
}
