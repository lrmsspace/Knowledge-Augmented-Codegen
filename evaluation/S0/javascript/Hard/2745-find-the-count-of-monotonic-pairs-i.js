// Source: https://leetcode.com/problems/find-the-count-of-monotonic-pairs-i/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of positive integers nums of length n.
//
// We call a pair of non-negative integer arrays (arr1, arr2) monotonic if:
//
//
// 	The lengths of both arrays are n.
// 	arr1 is monotonically non-decreasing, in other words, arr1[0] <= arr1[1] <= ... <= arr1[n - 1].
// 	arr2 is monotonically non-increasing, in other words, arr2[0] >= arr2[1] >= ... >= arr2[n - 1].
// 	arr1[i] + arr2[i] == nums[i] for all 0 <= i <= n - 1.
//
//
// Return the count of monotonic pairs.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [2,3,2]
//
// Output: 4
//
// Explanation:
//
// The good pairs are:
//
//
// 	([0, 1, 1], [2, 2, 1])
// 	([0, 1, 2], [2, 2, 0])
// 	([0, 2, 2], [2, 1, 0])
// 	([1, 2, 2], [1, 1, 0])
//
// Constraints:
// 1 <= n == nums.length <= 2000
// 	1 <= nums[i] <= 50
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var countOfPairs = function(nums) {
    const MOD = 1e9 + 7;
    const n = nums.length;
    const maxNum = Math.max(...nums);
    const dpInc = Array.from({ length: n + 1 }, () => Array(maxNum + 1).fill(0));
    const dpDec = Array.from({ length: n + 1 }, () => Array(maxNum + 1).fill(0));
    dpInc[0][0] = 1;

    for (let i = 1; i <= n; i++) {
        let prefixSum = 0;
        for (let j = 0; j <= nums[i - 1]; j++) {
            prefixSum = (prefixSum + dpInc[i - 1][j]) % MOD;
            dpInc[i][j] = prefixSum;
        }
    }
    dpDec[0][maxNum] = 1;

    for (let i = 1; i <= n; i++) {
        let suffixSum = 0;
        for (let j = maxNum; j >= maxNum - nums[i - 1]; j--) {
            suffixSum = (suffixSum + dpDec[i - 1][j]) % MOD;
            dpDec[i][j] = suffixSum;
        }
    }
    let result = 0;
    for (let j = 0; j <= maxNum; j++) {
        result = (result + (dpInc[n][j] * dpDec[n][j]) % MOD) % MOD;
    }
    return result;  
};
