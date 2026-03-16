// Source: https://leetcode.com/problems/minimum-score-after-removals-on-a-tree/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected connected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.
//
// You are given a 0-indexed integer array nums of length n where nums[i] represents the value of the ith node. You are also given a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// Remove two distinct edges of the tree to form three connected components. For a pair of removed edges, the following steps are defined:
//
//
// 	Get the XOR of all the values of the nodes for each of the three components respectively.
// 	The difference between the largest XOR value and the smallest XOR value is the score of the pair.
//
//
//
// 	For example, say the three components have the node values: [4,5,7], [1,9], and [3,3,3]. The three XOR values are 4 ^ 5 ^ 7 = 6, 1 ^ 9 = 8, and 3 ^ 3 ^ 3 = 3. The largest XOR value is 8 and the smallest XOR value is 3. The score is then 8 - 3 = 5.
//
//
// Return the minimum score of any possible pair of edge removals on the given tree.
//
// Example:
// Input: nums = [1,5,5,4,11], edges = [[0,1],[1,2],[1,3],[3,4]]
// Output: 9
// Explanation: The diagram above shows a way to make a pair of removals.
// - The 1st component has nodes [1,3,4] with values [5,4,11]. Its XOR value is 5 ^ 4 ^ 11 = 10.
// - The 2nd component has node [0] with value [1]. Its XOR value is 1 = 1.
// - The 3rd component has node [2] with value [5]. Its XOR value is 5 = 5.
// The score is the difference between the largest and smallest XOR value which is 10 - 1 = 9.
// It can be shown that no other pair of removals will obtain a smaller score than 9.
//
// Constraints:
// n == nums.length
// 	3 <= n <= 1000
// 	1 <= nums[i] <= 108
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	edges represents a valid tree.
//

int minimumScore(int* nums, int numsSize, int** edges, int edgesSize, int* edgesColSize) {
    int i;
    int **graph = (int**)calloc(numsSize, sizeof(int*));
    int *graphColSize = (int*)calloc(numsSize, sizeof(int));
    for (i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        graph[u] = (int*)realloc(graph[u], (graphColSize[u] + 1) * sizeof(int));
        graph[u][graphColSize[u]++] = v;
        graph[v] = (int*)realloc(graph[v], (graphColSize[v] + 1) * sizeof(int));
        graph[v][graphColSize[v]++] = u;
    }

    int *subtreeXor = (int*)calloc(numsSize, sizeof(int));
    int *parent = (int*)calloc(numsSize, sizeof(int));
    int *visited = (int*)calloc(numsSize, sizeof(int));

    // Post-order DFS to compute subtree XORs
    void dfs(int node) {
        visited[node] = 1;
        subtreeXor[node] = nums[node];
        for (i = 0; i < graphColSize[node]; i++) {
            int neighbor = graph[node][i];
            if (!visited[neighbor]) {
                parent[neighbor] = node;
                dfs(neighbor);
                subtreeXor[node] ^= subtreeXor[neighbor];
            }
        }
    }
    dfs(0);

    int totalXor = subtreeXor[0];
    int minScore = INT_MAX;

    // Try removing every pair of edges
    for (i = 0; i < edgesSize; i++) {
        int u1 = edges[i][0];
        int v1 = edges[i][1];
        if (parent[v1] == u1) {
            // v1 is child of u1
            int xor1 = subtreeXor[v1];
            for (int j = i + 1; j < edgesSize; j++) {
                int u2 = edges[j][0];
                int v2 = edges[j][1];
                if (parent[v2] == u2) {
                    // v2 is child of u2
                    int xor2 = subtreeXor[v2];
                    int xor3 = totalXor ^ xor1 ^ xor2;
                    int maxXor = fmax(xor1, fmax(xor2, xor3));
                    int minXor = fmin(xor1, fmin(xor2, xor3));
                    minScore = fmin(minScore, maxXor - minXor);
                } else {
                    // u2 is child of v2
                    int xor2 = subtreeXor[u2];
                    int xor3 = totalXor ^ xor1 ^ xor2;
                    int maxXor = fmax(xor1, fmax(xor2, xor3));
                    int minXor = fmin(xor1, fmin(xor2, xor3));
                    minScore = fmin(minScore, maxXor - minXor);
                }
            }
        } else {
            // u1 is child of v1
            int xor1 = subtreeXor[u1];
            for (int j = i + 1; j < edgesSize; j++) {
                int u2 = edges[j][0];
                int v2 = edges[j][1];
                if (parent[v2] == u2) {
                    // v2 is child of u2
                    int xor2 = subtreeXor[v2];
                    int xor3 = totalXor ^ xor1 ^ xor2;
                    int maxXor = fmax(xor1, fmax(xor2, xor3));
                    int minXor = fmin(xor1, fmin(xor2, xor3));
                    minScore = fmin(minScore, maxXor - minXor);
                } else {
                    // u2 is child of v2
                    int xor2 = subtreeXor[u2];
                    int xor3 = totalXor ^ xor1 ^ xor2;
                    int maxXor = fmax(xor1, fmax(xor2, xor3));
                    int minXor = fmin(xor1, fmin(xor2, xor3));
                    minScore = fmin(minScore, maxXor - minXor);
                }
            }
        }
    }
    // Cleanup
    for (i = 0; i < numsSize; i++) {
        free(graph[i]);
    }
    free(graph);
    free(graphColSize);
    free(subtreeXor);
    free(parent);
    free(visited);
    return minScore;
}
