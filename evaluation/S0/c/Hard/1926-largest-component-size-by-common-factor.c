// Source: https://leetcode.com/problems/largest-component-size-by-common-factor/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array of unique positive integers nums. Consider the following graph:
//
//
// 	There are nums.length nodes, labeled nums[0] to nums[nums.length - 1],
// 	There is an undirected edge between nums[i] and nums[j] if nums[i] and nums[j] share a common factor greater than 1.
//
//
// Return the size of the largest connected component in the graph.
//
// Example:
// Input: nums = [4,6,15,35]
// Output: 4
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= nums[i] <= 105
// 	All the values of nums are unique.
//

int largestComponentSize(int* nums, int numsSize) {
    /* Union-Find (Disjoint Set Union) implementation */
    int maxNum = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] > maxNum) maxNum = nums[i];
    }

    int *parent = (int*)malloc((maxNum + 1) * sizeof(int));
    int *rank = (int*)calloc((maxNum + 1), sizeof(int));
    if (!parent || !rank) {
        free(parent); free(rank);
        return 0;
    }
    for (int i = 0; i <= maxNum; ++i) parent[i] = i;

    // Find with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Union by rank
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

    // Union numbers by their prime factors
    for (int i = 0; i < numsSize; ++i) {
        int num = nums[i];
        for (int factor = 2; factor * factor <= num; ++factor) {
            if (num % factor == 0) {
                unionSet(num, factor);
                unionSet(num, num / factor);
            }
        }
    }

    // Count the size of each component
    int *count = (int*)calloc((maxNum + 1), sizeof(int));
    if (!count) {
        free(parent); free(rank);
        return 0;
    }
    int maxSize = 0;
    for (int i = 0; i < numsSize; ++i) {
        int root = find(nums[i]);
        count[root]++;
        if (count[root] > maxSize) {
            maxSize = count[root];
        }
    }

    free(parent);
    free(rank);     
    free(count);
    return maxSize;
}
