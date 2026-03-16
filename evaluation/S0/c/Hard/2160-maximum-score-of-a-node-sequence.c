// Source: https://leetcode.com/problems/maximum-score-of-a-node-sequence/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected graph with n nodes, numbered from 0 to n - 1.
//
// You are given a 0-indexed integer array scores of length n where scores[i] denotes the score of node i. You are also given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes ai and bi.
//
// A node sequence is valid if it meets the following conditions:
//
//
// 	There is an edge connecting every pair of adjacent nodes in the sequence.
// 	No node appears more than once in the sequence.
//
//
// The score of a node sequence is defined as the sum of the scores of the nodes in the sequence.
//
// Return the maximum score of a valid node sequence with a length of 4. If no such sequence exists, return -1.
//
// Example:
// Input: scores = [5,2,9,8,4], edges = [[0,1],[1,2],[2,3],[0,2],[1,3],[2,4]]
// Output: 24
// Explanation: The figure above shows the graph and the chosen node sequence [0,1,2,3].
// The score of the node sequence is 5 + 2 + 9 + 8 = 24.
// It can be shown that no other node sequence has a score of more than 24.
// Note that the sequences [3,1,2,0] and [1,0,2,3] are also valid and have a score of 24.
// The sequence [0,3,2,4] is not valid since no edge connects nodes 0 and 3.
//
// Constraints:
// n == scores.length
// 	4 <= n <= 5 * 104
// 	1 <= scores[i] <= 108
// 	0 <= edges.length <= 5 * 104
// 	edges[i].length == 2
// 	0 <= ai, bi <= n - 1
// 	ai != bi
// 	There are no duplicate edges.
//

int maximumScore(int* scores, int scoresSize, int** edges, int edgesSize, int* edgesColSize) {
    int n = scoresSize;
    /* build adjacency list with top 3 highest score neighbors for each node */
    int **adj = (int**)malloc(n * sizeof(int*));
    int *adjSizes = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        adj[i] = (int*)malloc(3 * sizeof(int));
    }
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1];
        /* insert v into u's adjacency list */
        for (int j = 0; j < adjSizes[u]; ++j) {
            if (scores[v] > scores[adj[u][j]]) {
                for (int k = adjSizes[u]; k > j; --k) {
                    if (k < 3) adj[u][k] = adj[u][k - 1];
                }
                adj[u][j] = v;
                if (adjSizes[u] < 3) adjSizes[u]++;
                break;
            }
        }
        if (adjSizes[u] < 3 && scores[v] <= scores[adj[u][adjSizes[u] - 1]]) {
            adj[u][adjSizes[u]++] = v;
        }
        /* insert u into v's adjacency list */
        for (int j = 0; j < adjSizes[v]; ++j) {
            if (scores[u] > scores[adj[v][j]]) {
                for (int k = adjSizes[v]; k > j; --k) {
                    if (k < 3) adj[v][k] = adj[v][k - 1];
                }
                adj[v][j] = u;
                if (adjSizes[v] < 3) adjSizes[v]++;
                break;
            }
        }
        if (adjSizes[v] < 3 && scores[u] <= scores[adj[v][adjSizes[v] - 1]]) {
            adj[v][adjSizes[v]++] = u;
        }
    }

    int maxScore = -1;
    /* try all edges as the middle edge of the sequence */
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1];
        for (int j = 0; j < adjSizes[u]; ++j) {
            int a = adj[u][j];
            if (a == v) continue;
            for (int k = 0; k < adjSizes[v]; ++k) {
                int b = adj[v][k];
                if (b == u || b == a) continue;
                int score = scores[a] + scores[u] + scores[v] + scores[b];
                if (score > maxScore) {
                    maxScore = score;
                }
            }
        }
    }
    /* cleanup */
    for (int i = 0; i < n; ++i) {
        free(adj[i]);
    }
    free(adj);
    free(adjSizes);
    return maxScore;
}
