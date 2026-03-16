// Source: https://leetcode.com/problems/sum-of-k-subarrays-with-length-at-least-m/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and two integers, k and m.
//
// Return the maximum sum of k non-overlapping subarrays of nums, where each subarray has a length of at least m.
//
// Example:
// Input: nums = [1,2,-1,3,3,4], k = 2, m = 2
//
// Output: 13
//
// Explanation:
//
// The optimal choice is:
//
//
// 	Subarray nums[3..5] with sum 3 + 3 + 4 = 10 (length is 3 >= m).
// 	Subarray nums[0..1] with sum 1 + 2 = 3 (length is 2 >= m).
//
//
// The total sum is 10 + 3 = 13.
//
// Constraints:
// 1 <= nums.length <= 2000
// 	-104 <= nums[i] <= 104
// 	1 <= k <= floor(nums.length / m)
// 	1 <= m <= 3
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @param {number} m
 * @return {number}
 */
var maxSum = function(nums, k, m) {
    const n = nums.length;
    const dp = Array.from({ length: k + 1 }, () => Array(n + 1).fill(-Infinity));
    dp[0][0] = 0;
    for (let i = 1; i <= k; i++) {
        for (let j = i * m; j <= n; j++) {
            let currentSum = 0;
            for (let l = j - 1; l >= (i - 1) * m; l--) {
                currentSum += nums[l];
                dp[i][j] = Math.max(dp[i][j], dp[i - 1][l] + currentSum);
            }
        }
    }
    return dp[k][n];    
};
