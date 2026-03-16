// Source: https://leetcode.com/problems/restore-the-array-from-adjacent-pairs/   |   Difficulty: Medium
//
// Problem Description:
// There is an integer array nums that consists of n unique elements, but you have forgotten it. However, you do remember every pair of adjacent elements in nums.
//
// You are given a 2D integer array adjacentPairs of size n - 1 where each adjacentPairs[i] = [ui, vi] indicates that the elements ui and vi are adjacent in nums.
//
// It is guaranteed that every adjacent pair of elements nums[i] and nums[i+1] will exist in adjacentPairs, either as [nums[i], nums[i+1]] or [nums[i+1], nums[i]]. The pairs can appear in any order.
//
// Return the original array nums. If there are multiple solutions, return any of them.
//
// Example:
// Input: adjacentPairs = [[2,1],[3,4],[3,2]]
// Output: [1,2,3,4]
// Explanation: This array has all its adjacent pairs in adjacentPairs.
// Notice that adjacentPairs[i] may not be in left-to-right order.
//
// Constraints:
// nums.length == n
// 	adjacentPairs.length == n - 1
// 	adjacentPairs[i].length == 2
// 	2 <= n <= 105
// 	-105 <= nums[i], ui, vi <= 105
// 	There exists some nums that has adjacentPairs as its pairs.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* restoreArray(int** adjacentPairs, int adjacentPairsSize, int* adjacentPairsColSize, int* returnSize) {
    // Create a map to store the adjacency list
    #define OFFSET 100000
    #define MAP_SIZE 200001
    int* map[MAP_SIZE] = {0};
    int mapSizes[MAP_SIZE] = {0};

    // Build the adjacency list from adjacentPairs
    for (int i = 0; i < adjacentPairsSize; i++) {
        int u = adjacentPairs[i][0] + OFFSET;
        int v = adjacentPairs[i][1] + OFFSET;

        map[u] = realloc(map[u], sizeof(int) * (mapSizes[u] + 1));
        map[u][mapSizes[u]++] = v;

        map[v] = realloc(map[v], sizeof(int) * (mapSizes[v] + 1));
        map[v][mapSizes[v]++] = u;
    }

    // Find the starting point (an endpoint of the array)
    int start = 0;
    for (int i = 0; i < MAP_SIZE; i++) {
        if (mapSizes[i] == 1) {
            start = i;
            break;
        }
    }

    // Restore the original array
    int n = adjacentPairsSize + 1;
    int* result = malloc(sizeof(int) * n);
    result[0] = start - OFFSET;

    for (int i = 1; i < n; i++) {
        int prev = result[i - 1] + OFFSET;
        for (int j = 0; j < mapSizes[prev]; j++) {
            int next = map[prev][j];
            if (i == 1 || next != result[i - 2] + OFFSET) {
                result[i] = next - OFFSET;
                break;
            }
        }
    }

    *returnSize = n;
    return result;      
}
