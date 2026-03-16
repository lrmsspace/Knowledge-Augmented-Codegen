// Source: https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array of positive integers nums and a positive integer limit.
//
// In one operation, you can choose any two indices i and j and swap nums[i] and nums[j] if |nums[i] - nums[j]| <= limit.
//
// Return the lexicographically smallest array that can be obtained by performing the operation any number of times.
//
// An array a is lexicographically smaller than an array b if in the first position where a and b differ, array a has an element that is less than the corresponding element in b. For example, the array [2,10,3] is lexicographically smaller than the array [10,2,3] because they differ at index 0 and 2 < 10.
//
// Example:
// Input: nums = [1,5,3,9,8], limit = 2
// Output: [1,3,5,8,9]
// Explanation: Apply the operation 2 times:
// - Swap nums[1] with nums[2]. The array becomes [1,3,5,9,8]
// - Swap nums[3] with nums[4]. The array becomes [1,3,5,8,9]
// We cannot obtain a lexicographically smaller array by applying any more operations.
// Note that it may be possible to get the same result by doing different operations.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= limit <= 109
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* lexicographicallySmallestArray(int* nums, int numsSize, int limit, int* returnSize) {
    // Disjoint Set Union (DSU) structure
    typedef struct {
        int *parent;
        int *rank;
    } DSU;

    DSU* createDSU(int size) {
        DSU* dsu = (DSU*)malloc(sizeof(DSU));
        dsu->parent = (int*)malloc(size * sizeof(int));
        dsu->rank = (int*)calloc(size, sizeof(int));
        for (int i = 0; i < size; i++) {
            dsu->parent[i] = i;
        }
        return dsu;
    }

    int find(DSU* dsu, int x) {
        if (dsu->parent[x] != x) {
            dsu->parent[x] = find(dsu, dsu->parent[x]);
        }
        return dsu->parent[x];
    }

    void unionSets(DSU* dsu, int x, int y) {
        int rootX = find(dsu, x);
        int rootY = find(dsu, y);
        if (rootX != rootY) {
            if (dsu->rank[rootX] > dsu->rank[rootY]) {
                dsu->parent[rootY] = rootX;
            } else if (dsu->rank[rootX] < dsu->rank[rootY]) {
                dsu->parent[rootX] = rootY;
            } else {
                dsu->parent[rootY] = rootX;
                dsu->rank[rootX]++;
            }
        }
    }

    // Create DSU
    DSU* dsu = createDSU(numsSize);

    // Union indices based on the limit condition
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (abs(nums[i] - nums[j]) <= limit) {
                unionSets(dsu, i, j);
            }
        }
    }

    // Group indices by their root parent
    #include <stdlib.h>
    #include <string.h>

    typedef struct {
        int* indices;
        int size;
        int capacity;
    } Group;

    Group* groups = (Group*)calloc(numsSize, sizeof(Group));
    for (int i = 0; i < numsSize; i++) {
        int root = find(dsu, i);
        if (groups[root].capacity == 0) {
            groups[root].capacity = 4;
            groups[root].indices = (int*)malloc(groups[root].capacity * sizeof(int));
        }
        if (groups[root].size == groups[root].capacity) {
            groups[root].capacity *= 2;
            groups[root].indices = (int*)realloc(groups[root].indices, groups[root].capacity * sizeof(int));
        }
        groups[root].indices[groups[root].size++] = i;
    }
    // Sort each group and place back into nums
    for (int i = 0; i < numsSize; i++) {
        if (groups[i].size > 0) {
            // Extract values
            int* values = (int*)malloc(groups[i].size * sizeof(int));
            for (int j = 0; j < groups[i].size; j++) {
                values[j] = nums[groups[i].indices[j]];
            }
            // Sort values
            qsort(values, groups[i].size, sizeof(int), (int (*)(const void*, const void*))strcmp);
            // Place back sorted values
            for (int j = 0; j < groups[i].size; j++) {
                nums[groups[i].indices[j]] = values[j];
            }
            free(values);
        }
    }
    // Cleanup
    for (int i = 0; i < numsSize; i++) {
        if (groups[i].capacity > 0) {
            free(groups[i].indices);
        }
    }
    free(groups);
    free(dsu->parent);
    free(dsu->rank);
    free(dsu);
    *returnSize = numsSize;
    return nums;
}
