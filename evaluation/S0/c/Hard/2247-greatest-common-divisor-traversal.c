// Source: https://leetcode.com/problems/greatest-common-divisor-traversal/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums, and you are allowed to traverse between its indices. You can traverse between index i and index j, i != j, if and only if gcd(nums[i], nums[j]) > 1, where gcd is the greatest common divisor.
//
// Your task is to determine if for every pair of indices i and j in nums, where i < j, there exists a sequence of traversals that can take us from i to j.
//
// Return true if it is possible to traverse between all such pairs of indices, or false otherwise.
//
// Example:
// Input: nums = [2,3,6]
// Output: true
// Explanation: In this example, there are 3 possible pairs of indices: (0, 1), (0, 2), and (1, 2).
// To go from index 0 to index 1, we can use the sequence of traversals 0 -> 2 -> 1, where we move from index 0 to index 2 because gcd(nums[0], nums[2]) = gcd(2, 6) = 2 > 1, and then move from index 2 to index 1 because gcd(nums[2], nums[1]) = gcd(6, 3) = 3 > 1.
// To go from index 0 to index 2, we can just go directly because gcd(nums[0], nums[2]) = gcd(2, 6) = 2 > 1. Likewise, to go from index 1 to index 2, we can just go directly because gcd(nums[1], nums[2]) = gcd(3, 6) = 3 > 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

bool canTraverseAllPairs(int* nums, int numsSize) {
    int maxNum = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] > maxNum) {
            maxNum = nums[i];
        }
    }

    int* spf = (int*)malloc((maxNum + 1) * sizeof(int));
    for (int i = 0; i <= maxNum; ++i) {
        spf[i] = i;
    }
    for (int i = 2; i * i <= maxNum; ++i) {
        if (spf[i] == i) {
            for (int j = i * i; j <= maxNum; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }

    int* parent = (int*)malloc((maxNum + 1) * sizeof(int));
    for (int i = 0; i <= maxNum; ++i) {
        parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unionSets(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA != rootB) {
            parent[rootB] = rootA;
        }
    }

    for (int i = 0; i < numsSize; ++i) {
        int num = nums[i];
        int firstFactor = spf[num];
        while (num > 1) {
            int factor = spf[num];
            unionSets(firstFactor, factor);
            while (num % factor == 0) {
                num /= factor;
            }
        }
    }

    int root = find(spf[nums[0]]);
    for (int i = 1; i < numsSize; ++i) {
        if (find(spf[nums[i]]) != root) {
            free(spf);
            free(parent);
            return false;
        }
    }

    free(spf);
    free(parent);
    return true;
}
