// Source: https://leetcode.com/problems/create-components-with-same-value/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 0 to n - 1.
//
// You are given a 0-indexed integer array nums of length n where nums[i] represents the value of the ith node. You are also given a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// You are allowed to delete some edges, splitting the tree into multiple connected components. Let the value of a component be the sum of all nums[i] for which node i is in the component.
//
// Return the maximum number of edges you can delete, such that every connected component in the tree has the same value.
//
// Example:
// Input: nums = [6,2,2,2,6], edges = [[0,1],[1,2],[1,3],[3,4]] 
// Output: 2 
// Explanation: The above figure shows how we can delete the edges [0,1] and [3,4]. The created components are nodes [0], [1,2,3] and [4]. The sum of the values in each component equals 6. It can be proven that no better deletion exists, so the answer is 2.
//
// Constraints:
// 1 <= n <= 2 * 104
// 	nums.length == n
// 	1 <= nums[i] <= 50
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= edges[i][0], edges[i][1] <= n - 1
// 	edges represents a valid tree.
//

int componentValue(int* nums, int numsSize, int** edges, int edgesSize, int* edgesColSize) {
    int total = 0;
    for (int i = 0; i < numsSize; ++i) total += nums[i];

    /* build adjacency list */
    int *adjSizes = (int*)calloc(numsSize, sizeof(int));
    int **adj = (int**)calloc(numsSize, sizeof(int*));
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1];
        adjSizes[u]++; adjSizes[v]++;
    }
    for (int i = 0; i < numsSize; ++i) {
        adj[i] = (int*)malloc(adjSizes[i] * sizeof(int));
        adjSizes[i] = 0; /* reuse for insertion index */
    }
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1];
        adj[u][adjSizes[u]++] = v;
        adj[v][adjSizes[v]++] = u;
    }

    int maxComponents = 0;
    for (int targetSum = 1; targetSum <= total / 2; ++targetSum) {
        if (total % targetSum != 0) continue;
        int components = total / targetSum;

        int *subtreeSums = (int*)calloc(numsSize, sizeof(int));
        int *visited = (int*)calloc(numsSize, sizeof(int));
        int *stack = (int*)malloc(numsSize * sizeof(int));
        int stackSize = 0;
        stack[stackSize++] = 0;
        visited[0] = 1;

        int valid = 1;
        while (stackSize > 0 && valid) {
            int node = stack[--stackSize];
            for (int i = 0; i < adjSizes[node]; ++i) {
                int neighbor = adj[node][i];
                if (!visited[neighbor]) {
                    visited[neighbor] = 1;
                    stack[stackSize++] = neighbor;
                }
            }
            subtreeSums[node] += nums[node];
            if (subtreeSums[node] > targetSum) {
                valid = 0;
                break;
            }
            if (subtreeSums[node] == targetSum) {
                subtreeSums[node] = 0; /* reset for parent */
            } else {
                for (int i = 0; i < adjSizes[node]; ++i) {
                    int neighbor = adj[node][i];
                    if (visited[neighbor]) {
                        subtreeSums[neighbor] += subtreeSums[node];
                        break;
                    }
                }
            }
        }
        if (valid && subtreeSums[0] == 0) {
            maxComponents = components;
        }
        free(subtreeSums);
        free(visited);
        free(stack);
        free(adjSizes);
        for (int i = 0; i < numsSize; ++i) {
            free(adj[i]);
        }
        free(adj);
        
    }
    return maxComponents;
}
