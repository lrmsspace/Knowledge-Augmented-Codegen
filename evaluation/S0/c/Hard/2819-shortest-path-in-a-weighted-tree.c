// Source: https://leetcode.com/problems/shortest-path-in-a-weighted-tree/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an undirected, weighted tree rooted at node 1 with n nodes numbered from 1 to n. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates an undirected edge from node ui to vi with weight wi.
//
// You are also given a 2D integer array queries of length q, where each queries[i] is either:
//
//
// 	[1, u, v, w'] – Update the weight of the edge between nodes u and v to w', where (u, v) is guaranteed to be an edge present in edges.
// 	[2, x] – Compute the shortest path distance from the root node 1 to node x.
//
//
// Return an integer array answer, where answer[i] is the shortest path distance from node 1 to x for the ith query of [2, x].
//
// Example:
// Input: n = 2, edges = [[1,2,7]], queries = [[2,2],[1,1,2,4],[2,2]]
//
// Output: [7,4]
//
// Explanation:
//
//
//
//
// 	Query [2,2]: The shortest path from root node 1 to node 2 is 7.
// 	Query [1,1,2,4]: The weight of edge (1,2) changes from 7 to 4.
// 	Query [2,2]: The shortest path from root node 1 to node 2 is 4.
//
// Constraints:
// 1 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi, wi]
// 	1 <= ui, vi <= n
// 	1 <= wi <= 104
// 	The input is generated such that edges represents a valid tree.
// 	1 <= queries.length == q <= 105
// 	queries[i].length == 2 or 4
// 	
// 		queries[i] == [1, u, v, w'] or,
// 		queries[i] == [2, x]
// 		1 <= u, v, x <= n
// 		(u, v) is always an edge from edges.
// 		1 <= w' <= 104
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* treeQueries(int n, int** edges, int edgesSize, int* edgesColSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
   
    // Build adjacency list
    typedef struct Edge {
        int to;
        int weight;
    } Edge;

    Edge** adj = (Edge**)malloc((n + 1) * sizeof(Edge*));
    int* adjSizes = (int*)calloc(n + 1, sizeof(int));
    for (int i = 0; i <= n; i++) {
        adj[i] = NULL;
    }

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        adj[u] = (Edge*)realloc(adj[u], (adjSizes[u] + 1) * sizeof(Edge));
        adj[u][adjSizes[u]++] = (Edge){v, w};

        adj[v] = (Edge*)realloc(adj[v], (adjSizes[v] + 1) * sizeof(Edge));
        adj[v][adjSizes[v]++] = (Edge){u, w};
    }

    // Precompute distances from root using DFS
    long long* distFromRoot = (long long*)malloc((n + 1) * sizeof(long long));
    bool* visited = (bool*)calloc(n + 1, sizeof(bool));

    void dfs(int node, long long currDist) {
        visited[node] = true;
        distFromRoot[node] = currDist;

        for (int i = 0; i < adjSizes[node]; i++) {
            Edge edge = adj[node][i];
            if (!visited[edge.to]) {
                dfs(edge.to, currDist + edge.weight);
            }
        }
    }

    dfs(1, 0);

    // Process queries
    int* result = (int*)malloc(queriesSize * sizeof(int));
    int resIndex = 0;

    for (int i = 0; i < queriesSize; i++) {
        if (queries[i][0] == 2) {
            int x = queries[i][1];
            result[resIndex++] = (int)distFromRoot[x];
        } else if (queries[i][0] == 1) {
            int u = queries[i][1];
            int v = queries[i][2];
            int newWeight = queries[i][3];

            // Find the edge and update its weight
            for (int j = 0; j < adjSizes[u]; j++) {
                if (adj[u][j].to == v) {
                    adj[u][j].weight = newWeight;
                    break;
                }
            }
            for (int j = 0; j < adjSizes[v]; j++) {
                if (adj[v][j].to == u) {
                    adj[v][j].weight = newWeight;
                    break;
                }
            }
            // Recompute distances from root
            memset(visited, 0, (n + 1) * sizeof(bool));
            dfs(1, 0);
        }
    }
    *returnSize = resIndex;
    // Free memory
    for (int i = 0; i <= n; i++) {
        free(adj[i]);
    }
    free(adj);
    free(adjSizes);
    free(distFromRoot);
    free(visited);
    return result; 
}
