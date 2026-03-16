// Source: https://leetcode.com/problems/minimize-hamming-distance-after-swap-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays, source and target, both of length n. You are also given an array allowedSwaps where each allowedSwaps[i] = [ai, bi] indicates that you are allowed to swap the elements at index ai and index bi (0-indexed) of array source. Note that you can swap elements at a specific pair of indices multiple times and in any order.
//
// The Hamming distance of two arrays of the same length, source and target, is the number of positions where the elements are different. Formally, it is the number of indices i for 0 <= i <= n-1 where source[i] != target[i] (0-indexed).
//
// Return the minimum Hamming distance of source and target after performing any amount of swap operations on array source.
//
// Example:
// Input: source = [1,2,3,4], target = [2,1,4,5], allowedSwaps = [[0,1],[2,3]]
// Output: 1
// Explanation: source can be transformed the following way:
// - Swap indices 0 and 1: source = [2,1,3,4]
// - Swap indices 2 and 3: source = [2,1,4,3]
// The Hamming distance of source and target is 1 as they differ in 1 position: index 3.
//
// Constraints:
// n == source.length == target.length
// 	1 <= n <= 105
// 	1 <= source[i], target[i] <= 105
// 	0 <= allowedSwaps.length <= 105
// 	allowedSwaps[i].length == 2
// 	0 <= ai, bi <= n - 1
// 	ai != bi
//

int minimumHammingDistance(int* source, int sourceSize, int* target, int targetSize, int** allowedSwaps, int allowedSwapsSize, int* allowedSwapsColSize) {
    // Union-Find (Disjoint Set Union) structure
    int* parent = (int*)malloc(sourceSize * sizeof(int));
    for (int i = 0; i < sourceSize; i++) {
        parent[i] = i;
    }

    // Find function with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Union function
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootY] = rootX;
        }
    }

    // Perform unions based on allowed swaps
    for (int i = 0; i < allowedSwapsSize; i++) {
        unionSets(allowedSwaps[i][0], allowedSwaps[i][1]);
    }

    // Map to store frequency of elements in each connected component
    #include <unordered_map>
    #include <vector>

    std::unordered_map<int, std::unordered_map<int, int>> componentMap;

    for (int i = 0; i < sourceSize; i++) {
        int root = find(i);
        componentMap[root][source[i]]++;
    }

    // Calculate minimum Hamming distance
    int hammingDistance = 0;

    for (int i = 0; i < targetSize; i++) {
        int root = find(i);
        if (componentMap[root][target[i]] > 0) {
            componentMap[root][target[i]]--;
        } else {
            hammingDistance++;
        }
    }

    free(parent);
    return hammingDistance;     
}
