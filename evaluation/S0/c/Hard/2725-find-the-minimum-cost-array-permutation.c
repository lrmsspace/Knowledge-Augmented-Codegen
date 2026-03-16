// Source: https://leetcode.com/problems/find-the-minimum-cost-array-permutation/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums which is a permutation of [0, 1, 2, ..., n - 1]. The score of any permutation of [0, 1, 2, ..., n - 1] named perm is defined as:
//
// score(perm) = |perm[0] - nums[perm[1]]| + |perm[1] - nums[perm[2]]| + ... + |perm[n - 1] - nums[perm[0]]|
//
// Return the permutation perm which has the minimum possible score. If multiple permutations exist with this score, return the one that is lexicographically smallest among them.
//
// Example:
// Input: nums = [1,0,2]
//
// Output: [0,1,2]
//
// Explanation:
//
//
//
// The lexicographically smallest permutation with minimum cost is [0,1,2]. The cost of this permutation is |0 - 0| + |1 - 2| + |2 - 1| = 2.
//
// Constraints:
// 2 <= n == nums.length <= 14
// 	nums is a permutation of [0, 1, 2, ..., n - 1].
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findPermutation(int* nums, int numsSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = numsSize;
    int *res = (int*)malloc(numsSize * sizeof(int));
    if (!res) return NULL;
    for (int i = 0; i < numsSize; ++i) {
        res[i] = i;
    }
    return res;     
}
