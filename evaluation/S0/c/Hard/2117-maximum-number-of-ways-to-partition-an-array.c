// Source: https://leetcode.com/problems/maximum-number-of-ways-to-partition-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums of length n. The number of ways to partition nums is the number of pivot indices that satisfy both conditions:
//
//
// 	1 <= pivot < n
// 	nums[0] + nums[1] + ... + nums[pivot - 1] == nums[pivot] + nums[pivot + 1] + ... + nums[n - 1]
//
//
// You are also given an integer k. You can choose to change the value of one element of nums to k, or to leave the array unchanged.
//
// Return the maximum possible number of ways to partition nums to satisfy both conditions after changing at most one element.
//
// Example:
// Input: nums = [2,-1,2], k = 3
// Output: 1
// Explanation: One optimal approach is to change nums[0] to k. The array becomes [3,-1,2].
// There is one way to partition the array:
// - For pivot = 2, we have the partition [3,-1 | 2]: 3 + -1 == 2.
//
// Constraints:
// n == nums.length
// 	2 <= n <= 105
// 	-105 <= k, nums[i] <= 105
//

int waysToPartition(int* nums, int numsSize, int k) {
    int n = numsSize;
    long totalSum = 0;
    for (int i = 0; i < n; i++) {
        totalSum += nums[i];
    }

    int* prefixDiffCount = (int*)calloc(n, sizeof(int));
    long prefixSum = 0;
    for (int i = 0; i < n - 1; i++) {
        prefixSum += nums[i];
        if (prefixSum * 2 == totalSum) {
            prefixDiffCount[i] = 1;
        }
    }

    for (int i = 1; i < n; i++) {
        prefixDiffCount[i] += prefixDiffCount[i - 1];
    }

    long maxWays = prefixDiffCount[n - 2];
    for (int i = 0; i < n; i++) {
        long newTotalSum = totalSum - nums[i] + k;
        long newPrefixSum = 0;
        long ways = 0;

        for (int j = 0; j < n - 1; j++) {
            if (j < i) {
                newPrefixSum += nums[j];
            } else if (j == i) {
                newPrefixSum += k;
            } else {
                newPrefixSum += nums[j];
            }

            if (newPrefixSum * 2 == newTotalSum) {
                ways++;
            }
        }

        if (ways > maxWays) {
            maxWays = ways;
        }
    }

    free(prefixDiffCount);
    return (int)maxWays;
}
