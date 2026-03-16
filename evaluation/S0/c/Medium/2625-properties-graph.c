// Source: https://leetcode.com/problems/properties-graph/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array properties having dimensions n x m and an integer k.
//
// Define a function intersect(a, b) that returns the number of distinct integers common to both arrays a and b.
//
// Construct an undirected graph where each index i corresponds to properties[i]. There is an edge between node i and node j if and only if intersect(properties[i], properties[j]) >= k, where i and j are in the range [0, n - 1] and i != j.
//
// Return the number of connected components in the resulting graph.
//
// Example:
// Input: properties = [[1,2],[1,1],[3,4],[4,5],[5,6],[7,7]], k = 1
//
// Output: 3
//
// Explanation:
//
// The graph formed has 3 connected components:
//
// Constraints:
// 1 <= n == properties.length <= 100
// 	1 <= m == properties[i].length <= 100
// 	1 <= properties[i][j] <= 100
// 	1 <= k <= m
//

int numberOfComponents(int** properties, int propertiesSize, int* propertiesColSize, int k) {
    int parent[propertiesSize];
    for (int i = 0; i < propertiesSize; i++) {
        parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void union_sets(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA != rootB) {
            parent[rootB] = rootA;
        }
    }

    int intersect(int* a, int* b, int size) {
        int count = 0;
        int freq[101] = {0};
        for (int i = 0; i < size; i++) {
            freq[a[i]]++;
        }
        for (int i = 0; i < size; i++) {
            if (freq[b[i]] > 0) {
                count++;
            }
        }
        return count;
    }

    for (int i = 0; i < propertiesSize; i++) {
        for (int j = i + 1; j < propertiesSize; j++) {
            if (intersect(properties[i], properties[j], propertiesColSize[i]) >= k) {
                union_sets(i, j);
            }
        }
    }

    int components = 0;
    for (int i = 0; i < propertiesSize; i++) {
        if (find(i) == i) {
            components++;
        }
    }

    return components;      
}
