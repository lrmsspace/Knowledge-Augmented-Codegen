// Source: https://leetcode.com/problems/find-the-sum-of-subsequence-powers/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums of length n, and a positive integer k.
//
// The power of a subsequence is defined as the minimum absolute difference between any two elements in the subsequence.
//
// Return the sum of powers of all subsequences of nums which have length equal to k.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,2,3,4], k = 3
//
// Output: 4
//
// Explanation:
//
// There are 4 subsequences in nums which have length 3: [1,2,3], [1,3,4], [1,2,4], and [2,3,4]. The sum of powers is |2 - 3| + |3 - 4| + |2 - 1| + |3 - 4| = 4.
//
// Constraints:
// 2 <= n == nums.length <= 50
// 	-108 <= nums[i] <= 108 
// 	2 <= k <= n
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var sumOfPowers = function(nums, k) {
    const mod = 1e9 + 7;
    const n = nums.length;
    nums.sort((a, b) => a - b);
    const dp = new Array(n).fill(0).map(() => new Array(k + 1).fill(0));
    for (let i = 0; i < n; i++) {
        dp[i][1] = 1;
        for (let j = 2; j <= k; j++) {
            for (let m = 0; m < i; m++) {
                dp[i][j] = (dp[i][j] + dp[m][j - 1] * (nums[i] - nums[m])) % mod;
            }
        }
    }
    let result = 0;
    for (let i = 0; i < n; i++) {
        result = (result + dp[i][k]) % mod;
    }
    return result;  
};
