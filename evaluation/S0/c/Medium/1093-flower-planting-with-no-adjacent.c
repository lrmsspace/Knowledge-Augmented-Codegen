// Source: https://leetcode.com/problems/flower-planting-with-no-adjacent/   |   Difficulty: Medium
//
// Problem Description:
// You have n gardens, labeled from 1 to n, and an array paths where paths[i] = [xi, yi] describes a bidirectional path between garden xi to garden yi. In each garden, you want to plant one of 4 types of flowers.
//
// All gardens have at most 3 paths coming into or leaving it.
//
// Your task is to choose a flower type for each garden such that, for any two gardens connected by a path, they have different types of flowers.
//
// Return any such a choice as an array answer, where answer[i] is the type of flower planted in the (i+1)th garden. The flower types are denoted 1, 2, 3, or 4. It is guaranteed an answer exists.
//
// Example:
// Input: n = 3, paths = [[1,2],[2,3],[3,1]]
// Output: [1,2,3]
// Explanation:
// Gardens 1 and 2 have different types.
// Gardens 2 and 3 have different types.
// Gardens 3 and 1 have different types.
// Hence, [1,2,3] is a valid answer. Other valid answers include [1,2,4], [1,4,2], and [3,2,1].
//
// Constraints:
// 1 <= n <= 104
// 	0 <= paths.length <= 2 * 104
// 	paths[i].length == 2
// 	1 <= xi, yi <= n
// 	xi != yi
// 	Every garden has at most 3 paths coming into or leaving it.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* gardenNoAdj(int n, int** paths, int pathsSize, int* pathsColSize, int* returnSize) {
    // Create adjacency list
    int** graph = (int**)malloc((n + 1) * sizeof(int*));
    int* graphColSize = (int*)calloc(n + 1, sizeof(int));
    for (int i = 0; i <= n; i++) {
        graph[i] = (int*)malloc(4 * sizeof(int)); // max 3 paths + 1 for safety
    }

    for (int i = 0; i < pathsSize; i++) {
        int u = paths[i][0];
        int v = paths[i][1];
        graph[u][graphColSize[u]++] = v;
        graph[v][graphColSize[v]++] = u;
    }

    // Result array
    int* result = (int*)malloc(n * sizeof(int));

    // Assign flowers
    for (int garden = 1; garden <= n; garden++) {
        int used[5] = {0}; // flower types 1 to 4

        // Mark used flower types by adjacent gardens
        for (int j = 0; j < graphColSize[garden]; j++) {
            int neighbor = graph[garden][j];
            if (result[neighbor - 1] != 0) {
                used[result[neighbor - 1]] = 1;
            }
        }

        // Assign the first available flower type
        for (int flowerType = 1; flowerType <= 4; flowerType++) {
            if (!used[flowerType]) {
                result[garden - 1] = flowerType;
                break;
            }
        }
    }

    // Free adjacency list memory
    for (int i = 0; i <= n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(graphColSize);

    *returnSize = n;
    return result;      
}
