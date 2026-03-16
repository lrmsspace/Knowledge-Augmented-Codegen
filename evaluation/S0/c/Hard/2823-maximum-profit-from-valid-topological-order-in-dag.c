// Source: https://leetcode.com/problems/maximum-profit-from-valid-topological-order-in-dag/   |   Difficulty: Hard
//
// Problem Description:
// You are given a Directed Acyclic Graph (DAG) with n nodes labeled from 0 to n - 1, represented by a 2D array edges, where edges[i] = [ui, vi] indicates a directed edge from node ui to vi. Each node has an associated score given in an array score, where score[i] represents the score of node i.
//
// You must process the nodes in a valid topological order. Each node is assigned a 1-based position in the processing order.
//
// The profit is calculated by summing up the product of each node's score and its position in the ordering.
//
// Return the maximum possible profit achievable with an optimal topological order.
//
// A topological order of a DAG is a linear ordering of its nodes such that for every directed edge u → v, node u comes before v in the ordering.
//
// Example:
// Input: n = 2, edges = [[0,1]], score = [2,3]
//
// Output: 8
//
// Explanation:
//
//
//
// Node 1 depends on node 0, so a valid order is [0, 1].
//
//
// 	
// 		
// 			Node
// 			Processing Order
// 			Score
// 			Multiplier
// 			Profit Calculation
// 		
// 	
// 	
// 		
// 			0
// 			1st
// 			2
// 			1
// 			2 × 1 = 2
// 		
// 		
// 			1
// 			2nd
// 			3
// 			2
// 			3 × 2 = 6
// 		
// 	
//
//
// The maximum total profit achievable over all valid topological orders is 2 + 6 = 8.
//
// Constraints:
// 1 <= n == score.length <= 22
// 	1 <= score[i] <= 105
// 	0 <= edges.length <= n * (n - 1) / 2
// 	edges[i] == [ui, vi] denotes a directed edge from ui to vi.
// 	0 <= ui, vi < n
// 	ui != vi
// 	The input graph is guaranteed to be a DAG.
// 	There are no duplicate edges.
//

int maxProfit(int n, int** edges, int edgesSize, int* edgesColSize, int* score, int scoreSize) {
    int totalStates = 1 << n;
    long long *dp = (long long*)calloc(totalStates, sizeof(long long));
    int *inDegree = (int*)calloc(n, sizeof(int));
    int **adj = (int**)malloc(n * sizeof(int*));
    int *adjSizes = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        adj[i] = (int*)malloc(n * sizeof(int));
    }

    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1];
        adj[u][adjSizes[u]++] = v;
        inDegree[v]++;
    }

    for (int state = 0; state < totalStates; ++state) {
        int position = __builtin_popcount(state) + 1;
        for (int node = 0; node < n; ++node) {
            if ((state & (1 << node)) == 0 && inDegree[node] == 0) {
                long long profit = dp[state] + (long long)score[node] * position;
                int nextState = state | (1 << node);
                if (profit > dp[nextState]) {
                    dp[nextState] = profit;
                }
                for (int j = 0; j < adjSizes[node]; ++j) {
                    int neighbor = adj[node][j];
                    inDegree[neighbor]--;
                }
            }
        }
        for (int node = 0; node < n; ++node) {
            if ((state & (1 << node)) == 0 && inDegree[node] == 0) {
                for (int j = 0; j < adjSizes[node]; ++j) {
                    int neighbor = adj[node][j];
                    inDegree[neighbor]++;
                }
            }
        }
    }

    long long result = dp[totalStates - 1];

    free(dp);
    free(inDegree);
    for (int i = 0; i < n; ++i) {
        free(adj[i]);
    }
    free(adj);
    free(adjSizes);

    return (int)result;
}
