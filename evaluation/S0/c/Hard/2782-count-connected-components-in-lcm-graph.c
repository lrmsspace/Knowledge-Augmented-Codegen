// Source: https://leetcode.com/problems/count-connected-components-in-lcm-graph/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of integers nums of size n and a positive integer threshold.
//
// There is a graph consisting of n nodes with the ith node having a value of nums[i]. Two nodes i and j in the graph are connected via an undirected edge if lcm(nums[i], nums[j]) <= threshold.
//
// Return the number of connected components in this graph.
//
// A connected component is a subgraph of a graph in which there exists a path between any two vertices, and no vertex of the subgraph shares an edge with a vertex outside of the subgraph.
//
// The term lcm(a, b) denotes the least common multiple of a and b.
//
// Example:
// Input: nums = [2,4,8,3,9], threshold = 5
//
// Output: 4
//
// Explanation: 
//
//
//
//  
//
// The four connected components are (2, 4), (3), (8), (9).
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	All elements of nums are unique.
// 	1 <= threshold <= 2 * 105
//

int countComponents(int* nums, int numsSize, int threshold) {
    if (numsSize <= 0) return 0;

    int maxNum = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] > maxNum) maxNum = nums[i];
    }

    int size = maxNum + 1;
    int *parent = (int*)malloc(size * sizeof(int));
    int *rank = (int*)malloc(size * sizeof(int));
    if (!parent || !rank) {
        free(parent); free(rank); return 0;
    }
    for (int i = 0; i < size; ++i) {
        parent[i] = i;
        rank[i] = 1;
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unionSet(int x, int y) {
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

    /* Union nodes based on LCM condition */
    for (int i = 0; i < numsSize; ++i) {
        int num = nums[i];
        for (int multiple = num; multiple <= threshold; multiple += num) {
            unionSet(num, multiple);
        }
    }

    /* Count unique components */
    int components = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (find(nums[i]) == nums[i]) {
            components++;
        }
    }

    free(parent);
    free(rank);
    return components;      
}
