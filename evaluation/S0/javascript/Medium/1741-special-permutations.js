// Source: https://leetcode.com/problems/special-permutations/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums containing n distinct positive integers. A permutation of nums is called special if:
//
//
// 	For all indexes 0 <= i < n - 1, either nums[i] % nums[i+1] == 0 or nums[i+1] % nums[i] == 0.
//
//
// Return the total number of special permutations. As the answer could be large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [2,3,6]
// Output: 2
// Explanation: [3,6,2] and [2,6,3] are the two special permutations of nums.
//
// Constraints:
// 2 <= nums.length <= 14
// 	1 <= nums[i] <= 109
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var specialPerm = function(nums) {
    const n = nums.length;
    const mod = 1e9 + 7;
    const dp = Array.from({ length: 1 << n }, () => new Array(n).fill(0));  
    for (let i = 0; i < n; i++) {
        dp[1 << i][i] = 1;  
    }
    for (let mask = 1; mask < (1 << n); mask++) {
        for (let last = 0; last < n; last++) {
            if ((mask & (1 << last)) === 0) continue;  
            for (let next = 0; next < n; next++) {
                if ((mask & (1 << next)) !== 0) continue;  
                if (nums[last] % nums[next] === 0 || nums[next] % nums[last] === 0) {
                    dp[mask | (1 << next)][next] = (dp[mask | (1 << next)][next] + dp[mask][last]) % mod;
                }
            }
        }
    }
    let result = 0;
    for (let i = 0; i < n; i++) {
        result = (result + dp[(1 << n) - 1][i]) % mod;
    }
    return result;
};
