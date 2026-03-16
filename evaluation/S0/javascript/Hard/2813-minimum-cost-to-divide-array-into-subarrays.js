// Source: https://leetcode.com/problems/minimum-cost-to-divide-array-into-subarrays/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integer arrays, nums and cost, of the same size, and an integer k.
//
// You can divide nums into subarrays. The cost of the ith subarray consisting of elements nums[l..r] is:
//
//
// 	(nums[0] + nums[1] + ... + nums[r] + k * i) * (cost[l] + cost[l + 1] + ... + cost[r]).
//
//
// Note that i represents the order of the subarray: 1 for the first subarray, 2 for the second, and so on.
//
// Return the minimum total cost possible from any valid division.
//
// Example:
// Input: nums = [3,1,4], cost = [4,6,6], k = 1
//
// Output: 110
//
// Explanation:
// The minimum total cost possible can be achieved by dividing nums into subarrays [3, 1] and [4].
//
//
// 	The cost of the first subarray [3,1] is (3 + 1 + 1 * 1) * (4 + 6) = 50.
// 	The cost of the second subarray [4] is (3 + 1 + 4 + 1 * 2) * 6 = 60.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	cost.length == nums.length
// 	1 <= nums[i], cost[i] <= 1000
// 	1 <= k <= 1000
//

/**
 * @param {number[]} nums
 * @param {number[]} cost
 * @param {number} k
 * @return {number}
 */
var minimumCost = function(nums, cost, k) {
    const n = nums.length;
    const prefixNums = Array(n + 1).fill(0);
    const prefixCost = Array(n + 1).fill(0);
    for (let i = 0; i < n; i++) {
        prefixNums[i + 1] = prefixNums[i] + nums[i];
        prefixCost[i + 1] = prefixCost[i] + cost[i];
    }
    const dp = Array(n + 1).fill(Infinity);
    dp[0] = 0;
    for (let i = 1; i <= n; i++) {
        for (let j = 0; j < i; j++) {
            const subarraySum = prefixNums[i] - prefixNums[j];
            const subarrayCost = prefixCost[i] - prefixCost[j];
            const subarrayIndex = i - j;
            dp[i] = Math.min(dp[i], dp[j] + (subarraySum + k * subarrayIndex) * subarrayCost);
        }
    }
    return dp[n];
};
