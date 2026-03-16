// Source: https://leetcode.com/problems/divide-nodes-into-the-maximum-number-of-groups/   |   Difficulty: Hard
//
// Problem Description:
// You are given a positive integer n representing the number of nodes in an undirected graph. The nodes are labeled from 1 to n.
//
// You are also given a 2D integer array edges, where edges[i] = [ai, bi] indicates that there is a bidirectional edge between nodes ai and bi. Notice that the given graph may be disconnected.
//
// Divide the nodes of the graph into m groups (1-indexed) such that:
//
//
// 	Each node in the graph belongs to exactly one group.
// 	For every pair of nodes in the graph that are connected by an edge [ai, bi], if ai belongs to the group with index x, and bi belongs to the group with index y, then |y - x| = 1.
//
//
// Return the maximum number of groups (i.e., maximum m) into which you can divide the nodes. Return -1 if it is impossible to group the nodes with the given conditions.
//
// Example:
// Input: n = 6, edges = [[1,2],[1,4],[1,5],[2,6],[2,3],[4,6]]
// Output: 4
// Explanation: As shown in the image we:
// - Add node 5 to the first group.
// - Add node 1 to the second group.
// - Add nodes 2 and 4 to the third group.
// - Add nodes 3 and 6 to the fourth group.
// We can see that every edge is satisfied.
// It can be shown that that if we create a fifth group and move any node from the third or fourth group to it, at least on of the edges will not be satisfied.
//
// Constraints:
// 1 <= n <= 500
// 	1 <= edges.length <= 104
// 	edges[i].length == 2
// 	1 <= ai, bi <= n
// 	ai != bi
// 	There is at most one edge between any pair of vertices.
//

int magnificentSets(int n, int** edges, int edgesSize, int* edgesColSize) {
    // Build adjacency list
    int** graph = (int**)malloc((n + 1) * sizeof(int*));
    int* graphSizes = (int*)calloc(n + 1, sizeof(int));
    for (int i = 0; i <= n; i++) {
        graph[i] = (int*)malloc(n * sizeof(int));
    }
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        graph[u][graphSizes[u]++] = v;
        graph[v][graphSizes[v]++] = u;
    }

    int* visited = (int*)calloc(n + 1, sizeof(int));
    int result = 0;

    for (int i = 1; i <= n; i++) {
        if (visited[i]) continue;

        // BFS to check bipartiteness and find max depth
        int queue[n + 1];
        int front = 0, back = 0;
        queue[back++] = i;
        visited[i] = 1;
        int depth[n + 1];
        depth[i] = 1;
        int maxDepth = 1;

        while (front < back) {
            int node = queue[front++];
            for (int j = 0; j < graphSizes[node]; j++) {
                int neighbor = graph[node][j];
                if (!visited[neighbor]) {
                    visited[neighbor] = visited[node] % 2 + 1;
                    depth[neighbor] = depth[node] + 1;
                    if (depth[neighbor] > maxDepth) {
                        maxDepth = depth[neighbor];
                    }
                    queue[back++] = neighbor;
                } else if (visited[neighbor] == visited[node]) {
                    // Not bipartite
                    for (int k = 0; k <= n; k++) free(graph[k]);
                    free(graph);
                    free(graphSizes);
                    free(visited);
                    return -1;
                }
            }
        }
        result += maxDepth;
    }

    for (int i = 0; i <= n; i++) free(graph[i]);
    free(graph);
    free(graphSizes);
    free(visited);
    return result;
}
