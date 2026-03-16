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

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var waysToPartition = function(nums, k) {
    const n = nums.length;
    const prefixSums = new Array(n).fill(0);
    prefixSums[0] = nums[0];
    for (let i = 1; i < n; i++) {
        prefixSums[i] = prefixSums[i - 1] + nums[i];
    }
    const totalSum = prefixSums[n - 1];

    const countMap = new Map();
    for (let pivot = 1; pivot < n; pivot++) {
        const leftSum = prefixSums[pivot - 1];
        const rightSum = totalSum - leftSum;
        if (leftSum === rightSum) {
            countMap.set(pivot, (countMap.get(pivot) || 0) + 1);
        }
    }

    let maxWays = countMap.size;
    for (let i = 0; i < n; i++) {
        const originalValue = nums[i];
        const newValue = k;
        const delta = newValue - originalValue;
        for (let pivot = 1; pivot < n; pivot++) {
            const leftSum = prefixSums[pivot - 1];
            const rightSum = totalSum - leftSum;
            if (i < pivot) {
                if (leftSum + delta === rightSum) {
                    maxWays = Math.max(maxWays, (countMap.get(pivot) || 0) + 1);
                } else if (leftSum === rightSum) {
                    maxWays = Math.max(maxWays, (countMap.get(pivot) || 0) - 1);
                }
            } else {
                if (leftSum === rightSum + delta) {
                    maxWays = Math.max(maxWays, (countMap.get(pivot) || 0) + 1);
                } else if (leftSum === rightSum) {
                    maxWays = Math.max(maxWays, (countMap.get(pivot) || 0) - 1);
                }
            }
        }
    }
    return maxWays; 
};
