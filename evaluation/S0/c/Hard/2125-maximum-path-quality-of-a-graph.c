// Source: https://leetcode.com/problems/maximum-path-quality-of-a-graph/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected graph with n nodes numbered from 0 to n - 1 (inclusive). You are given a 0-indexed integer array values where values[i] is the value of the ith node. You are also given a 0-indexed 2D integer array edges, where each edges[j] = [uj, vj, timej] indicates that there is an undirected edge between the nodes uj and vj, and it takes timej seconds to travel between the two nodes. Finally, you are given an integer maxTime.
//
// A valid path in the graph is any path that starts at node 0, ends at node 0, and takes at most maxTime seconds to complete. You may visit the same node multiple times. The quality of a valid path is the sum of the values of the unique nodes visited in the path (each node's value is added at most once to the sum).
//
// Return the maximum quality of a valid path.
//
// Note: There are at most four edges connected to each node.
//
// Example:
// Input: values = [0,32,10,43], edges = [[0,1,10],[1,2,15],[0,3,10]], maxTime = 49
// Output: 75
// Explanation:
// One possible path is 0 -> 1 -> 0 -> 3 -> 0. The total time taken is 10 + 10 + 10 + 10 = 40 <= 49.
// The nodes visited are 0, 1, and 3, giving a maximal path quality of 0 + 32 + 43 = 75.
//
// Constraints:
// n == values.length
// 	1 <= n <= 1000
// 	0 <= values[i] <= 108
// 	0 <= edges.length <= 2000
// 	edges[j].length == 3 
// 	0 <= uj < vj <= n - 1
// 	10 <= timej, maxTime <= 100
// 	All the pairs [uj, vj] are unique.
// 	There are at most four edges connected to each node.
// 	The graph may not be connected.
//

int maximalPathQuality(int* values, int valuesSize, int** edges, int edgesSize, int* edgesColSize, int maxTime) {
    int **graph = (int**)calloc(valuesSize, sizeof(int*));
    int *graphColSize = (int*)calloc(valuesSize, sizeof(int));
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0], v = edges[i][1], t = edges[i][2];
        graph[u] = (int*)realloc(graph[u], (graphColSize[u] + 1) * 3 * sizeof(int));
        graph[u][graphColSize[u] * 3 + 0] = v;
        graph[u][graphColSize[u] * 3 + 1] = t;
        graph[u][graphColSize[u] * 3 + 2] = 1; /* mark as unvisited */
        graphColSize[u]++;
        graph[v] = (int*)realloc(graph[v], (graphColSize[v] + 1) * 3 * sizeof(int));
        graph[v][graphColSize[v] * 3 + 0] = u;
        graph[v][graphColSize[v] * 3 + 1] = t;
        graph[v][graphColSize[v] * 3 + 2] = 1; /* mark as unvisited */
        graphColSize[v]++;
    }

    int maxQuality = 0;
    int currQuality = values[0];
    void dfs(int node, int timeLeft) {
        if (node == 0) {
            if (currQuality > maxQuality) maxQuality = currQuality;
        }
        for (int i = 0; i < graphColSize[node]; i++) {
            int neighbor = graph[node][i * 3 + 0];
            int travelTime = graph[node][i * 3 + 1];
            int visitedFlagIndex = i * 3 + 2;
            if (travelTime <= timeLeft) {
                int firstVisit = (graph[node][visitedFlagIndex] == 1) ? 1 : 0;
                if (firstVisit) {
                    currQuality += values[neighbor];
                    graph[node][visitedFlagIndex] = 0; /* mark as visited */
                }
                dfs(neighbor, timeLeft - travelTime);
                if (firstVisit) {
                    currQuality -= values[neighbor];
                    graph[node][visitedFlagIndex] = 1; /*       
mark as unvisited */
                }
            }
        }
    }

    dfs(0, maxTime);

    for (int i = 0; i < valuesSize; i++) {
        free(graph[i]);
    }
    free(graph);
    free(graphColSize);

    return maxQuality;
}
