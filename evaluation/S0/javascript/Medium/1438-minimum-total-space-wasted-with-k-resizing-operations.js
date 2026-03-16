// Source: https://leetcode.com/problems/minimum-total-space-wasted-with-k-resizing-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are currently designing a dynamic array. You are given a 0-indexed integer array nums, where nums[i] is the number of elements that will be in the array at time i. In addition, you are given an integer k, the maximum number of times you can resize the array (to any size).
//
// The size of the array at time t, sizet, must be at least nums[t] because there needs to be enough space in the array to hold all the elements. The space wasted at time t is defined as sizet - nums[t], and the total space wasted is the sum of the space wasted across every time t where 0 <= t < nums.length.
//
// Return the minimum total space wasted if you can resize the array at most k times.
//
// Note: The array can have any size at the start and does not count towards the number of resizing operations.
//
// Example:
// Input: nums = [10,20], k = 0
// Output: 10
// Explanation: size = [20,20].
// We can set the initial size to be 20.
// The total wasted space is (20 - 10) + (20 - 20) = 10.
//
// Constraints:
// 1 <= nums.length <= 200
// 	1 <= nums[i] <= 106
// 	0 <= k <= nums.length - 1
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var minSpaceWastedKResizing = function(nums, k) {
    const n = nums.length;
    const dp = Array.from({ length: n + 1 }, () => Array(k + 1).fill(Infinity));
    dp[0][0] = 0;
    for (let i = 1; i <= n; i++) {
        for (let j = 0; j <= Math.min(i - 1, k); j++) {
            let maxNum = 0;
            let totalWasted = 0;
            for (let m = i; m >= 1; m--) {
                maxNum = Math.max(maxNum, nums[m - 1]);
                totalWasted += maxNum - nums[m - 1];
                dp[i][j] = Math.min(dp[i][j], dp[m - 1][j - (m > 1 ? 1 : 0)] + totalWasted);
            }
        }
    }
    return dp[n][k];
};
