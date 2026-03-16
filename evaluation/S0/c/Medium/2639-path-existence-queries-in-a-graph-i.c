// Source: https://leetcode.com/problems/path-existence-queries-in-a-graph-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n representing the number of nodes in a graph, labeled from 0 to n - 1.
//
// You are also given an integer array nums of length n sorted in non-decreasing order, and an integer maxDiff.
//
// An undirected edge exists between nodes i and j if the absolute difference between nums[i] and nums[j] is at most maxDiff (i.e., |nums[i] - nums[j]| <= maxDiff).
//
// You are also given a 2D integer array queries. For each queries[i] = [ui, vi], determine whether there exists a path between nodes ui and vi.
//
// Return a boolean array answer, where answer[i] is true if there exists a path between ui and vi in the ith query and false otherwise.
//
// Example:
// Input: n = 2, nums = [1,3], maxDiff = 1, queries = [[0,0],[0,1]]
//
// Output: [true,false]
//
// Explanation:
//
//
// 	Query [0,0]: Node 0 has a trivial path to itself.
// 	Query [0,1]: There is no edge between Node 0 and Node 1 because |nums[0] - nums[1]| = |1 - 3| = 2, which is greater than maxDiff.
// 	Thus, the final answer after processing all the queries is [true, false].
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	0 <= nums[i] <= 105
// 	nums is sorted in non-decreasing order.
// 	0 <= maxDiff <= 105
// 	1 <= queries.length <= 105
// 	queries[i] == [ui, vi]
// 	0 <= ui, vi < n
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* pathExistenceQueries(int n, int* nums, int numsSize, int maxDiff, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    // Union-Find (Disjoint Set Union) Data Structure
    int* parent = (int*)malloc(n * sizeof(int));
    int* rank = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    // Find function with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Union function with union by rank
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    // Build the graph using union-find
    for (int i = 0; i < n - 1; i++) {
        if (nums[i + 1] - nums[i] <= maxDiff) {
            unionSets(i, i + 1);
        }
    }

    // Process the queries
    bool* result = (bool*)malloc(queriesSize * sizeof(bool));
    for (int i = 0; i < queriesSize; i++) {
        int u = queries[i][0];
        int v = queries[i][1];
        result[i] = (find(u) == find(v));
    }

    // Clean up
    free(parent);
    free(rank);

    *returnSize = queriesSize;
    return result;      
}
