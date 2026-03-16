// Source: https://leetcode.com/problems/find-the-sum-of-the-power-of-all-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums of length n and a positive integer k.
//
// The power of an array of integers is defined as the number of subsequences with their sum equal to k.
//
// Return the sum of power of all subsequences of nums.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input:   nums = [1,2,3], k = 3 
//
// Output:   6 
//
// Explanation:
//
// There are 5 subsequences of nums with non-zero power:
//
//
// 	The subsequence [1,2,3] has 2 subsequences with sum == 3: [1,2,3] and [1,2,3].
// 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
// 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
// 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
// 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
//
//
// Hence the answer is 2 + 1 + 1 + 1 + 1 = 6.
//
// Constraints:
// 1 <= n <= 100
// 	1 <= nums[i] <= 104
// 	1 <= k <= 100
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var sumOfPower = function(nums, k) {
    const mod = 1e9 + 7;
    const n = nums.length;
    const dp = new Array(n + 1).fill(0).map(() => new Array(k + 1).fill(0));
    dp[0][0] = 1;
    for (let i = 1; i <= n; i++) {
        for (let j = 0; j <= k; j++) {
            dp[i][j] = (dp[i - 1][j] + (j >= nums[i - 1] ? dp[i - 1][j - nums[i - 1]] : 0)) % mod;
        }
    }
    let result = 0;
    for (let i = 1; i <= n; i++) {
        result = (result + dp[i][k]) % mod;
    }
    return result;  
};
