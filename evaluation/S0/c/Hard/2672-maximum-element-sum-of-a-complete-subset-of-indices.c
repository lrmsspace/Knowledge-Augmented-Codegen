// Source: https://leetcode.com/problems/maximum-element-sum-of-a-complete-subset-of-indices/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 1-indexed array nums. Your task is to select a complete subset from nums where every pair of selected indices multiplied is a perfect square,. i. e. if you select ai and aj, i * j must be a perfect square.
//
// Return the sum of the complete subset with the maximum sum.
//
// Example:
// Input: nums = [8,7,3,5,7,2,4,9]
//
// Output: 16
//
// Explanation:
//
// We select elements at indices 2 and 8 and 2 * 8 is a perfect square.
//
// Constraints:
// 1 <= n == nums.length <= 104
// 	1 <= nums[i] <= 109
//

long long maximumSum(int* nums, int numsSize) {
    int maxIdx = numsSize;
    int *group = (int*)malloc((maxIdx + 1) * sizeof(int));
    if (!group) return 0;
    for (int i = 1; i <= maxIdx; ++i) group[i] = i;

    for (int i = 1; i * i <= maxIdx; ++i) {
        int square = i * i;
        for (int j = 1; j * square <= maxIdx; ++j) {
            int a = j;
            int b = j * square;
            while (group[a] != a) a = group[a];
            while (group[b] != b) b = group[b];
            if (a != b) group[b] = a;
        }
    }

    long long *sums = (long long*)calloc((maxIdx + 1), sizeof(long long));
    if (!sums) {
        free(group);
        return 0;
    }

    for (int i = 1; i <= maxIdx; ++i) {
        int root = i;
        while (group[root] != root) root = group[root];
        sums[root] += nums[i - 1];
    }

    long long maxSum = 0;
    for (int i = 1; i <= maxIdx; ++i) {
        if (sums[i] > maxSum) {
            maxSum = sums[i];
        }
    }

    free(group);
    free(sums);
    return maxSum;      
}
