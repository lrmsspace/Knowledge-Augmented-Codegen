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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* eventualSafeNodes(int** graph, int graphSize, int* graphColSize, int* returnSize) {
    int *color = (int *)calloc(graphSize, sizeof(int));
    int *res = (int *)malloc(graphSize * sizeof(int));
    int resSize = 0;

    bool dfs(int node) {
        if (color[node] > 0) {
            return color[node] == 2;
        }
        color[node] = 1; // visiting
        for (int i = 0; i < graphColSize[node]; i++) {
            int neighbor = graph[node][i];
            if (color[neighbor] == 2) {
                continue;
            }
            if (color[neighbor] == 1 || !dfs(neighbor)) {
                return false;
            }
        }
        color[node] = 2; // safe
        return true;
    }

    for (int i = 0; i < graphSize; i++) {
        if (dfs(i)) {
            res[resSize++] = i;
        }
    }

    *returnSize = resSize;
    return res;     
}
