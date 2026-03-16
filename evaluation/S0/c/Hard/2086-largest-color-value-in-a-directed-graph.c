// Source: https://leetcode.com/problems/largest-color-value-in-a-directed-graph/   |   Difficulty: Hard
//
// Problem Description:
// There is a directed graph of n colored nodes and m edges. The nodes are numbered from 0 to n - 1.
//
// You are given a string colors where colors[i] is a lowercase English letter representing the color of the ith node in this graph (0-indexed). You are also given a 2D array edges where edges[j] = [aj, bj] indicates that there is a directed edge from node aj to node bj.
//
// A valid path in the graph is a sequence of nodes x1 -> x2 -> x3 -> ... -> xk such that there is a directed edge from xi to xi+1 for every 1 <= i < k. The color value of the path is the number of nodes that are colored the most frequently occurring color along that path.
//
// Return the largest color value of any valid path in the given graph, or -1 if the graph contains a cycle.
//
// Example:
// Input: colors = "abaca", edges = [[0,1],[0,2],[2,3],[3,4]]
// Output: 3
// Explanation: The path 0 -> 2 -> 3 -> 4 contains 3 nodes that are colored "a" (red in the above image).
//
// Constraints:
// n == colors.length
// 	m == edges.length
// 	1 <= n <= 105
// 	0 <= m <= 105
// 	colors consists of lowercase English letters.
// 	0 <= aj, bj < n
//



int largestPathValue(char * colors, int** edges, int edgesSize, int* edgesColSize){
    int n = strlen(colors);
    int (*adj)[n]; // adjacency matrix
    adj = malloc(n * sizeof(*adj));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
    }
    int *indegree = malloc(n * sizeof(int));
    memset(indegree, 0, n * sizeof(int));

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u][v] = 1;
        indegree[v]++;
    }

    int (*dp)[26]; // dp[i][c]: max count of color c ending at node i
    dp = malloc(n * sizeof(*dp));
    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++) {
            dp[i][c] = 0;
        }
    }

    int *queue = malloc(n * sizeof(int));
    int front = 0, back = 0;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            queue[back++] = i;
        }
    }

    int processed = 0;
    int maxColorValue = 0;

    while (front < back) {
        int u = queue[front++];
        processed++;

        int colorIndex = colors[u] - 'a';
        dp[u][colorIndex]++;
        if (dp[u][colorIndex] > maxColorValue) {
            maxColorValue = dp[u][colorIndex];
        }

        for (int v = 0; v < n; v++) {
            if (adj[u][v]) {
                for (int c = 0; c < 26; c++) {
                    if (dp[u][c] > dp[v][c]) {
                        dp[v][c] = dp[u][c];
                    }
                }
                indegree[v]--;
                if (indegree[v] == 0) {
                    queue[back++] = v;
                }
            }
        }
    }

    free(adj);
    free(indegree);
    free(dp);
    free(queue);
    return processed == n ? maxColorValue : -1;
}
