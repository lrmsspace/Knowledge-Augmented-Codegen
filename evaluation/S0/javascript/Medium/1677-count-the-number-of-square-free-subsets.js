// Source: https://leetcode.com/problems/count-the-number-of-square-free-subsets/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer 0-indexed array nums.
//
// A subset of the array nums is square-free if the product of its elements is a square-free integer.
//
// A square-free integer is an integer that is divisible by no square number other than 1.
//
// Return the number of square-free non-empty subsets of the array nums. Since the answer may be too large, return it modulo 109 + 7.
//
// A non-empty subset of nums is an array that can be obtained by deleting some (possibly none but not all) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.
//
// Example:
// Input: nums = [3,4,4,5]
// Output: 3
// Explanation: There are 3 square-free subsets in this example:
// - The subset consisting of the 0th element [3]. The product of its elements is 3, which is a square-free integer.
// - The subset consisting of the 3rd element [5]. The product of its elements is 5, which is a square-free integer.
// - The subset consisting of 0th and 3rd elements [3,5]. The product of its elements is 15, which is a square-free integer.
// It can be proven that there are no more than 3 square-free subsets in the given array.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 30
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var squareFreeSubsets = function(nums) {
    const MOD = 1e9 + 7;
    const primeMasks = [
        0,  // 0
        0,  // 1
        1,  // 2
        2,  // 3
        4,  // 4 (not square-free)
        8,  // 5
        16, // 6
        0,  // 7 (not square-free)
        32, // 8 (not square-free)
        64, // 9 (not square-free)
        128,// 10
        256,// 11
        0,  // 12 (not square-free)
        512,// 13
        1024,// 14
        0,  // 15 (not square-free)
        2048,// 16 (not square-free)
        4096,// 17
        0,  // 18 (not square-free)
        8192,// 19
        16384,// 20 (not square-free)
        32768,// 21 (not square-free)
        65536,// 22 (not square-free)
        131072,// 23
        0,  // 24 (not square-free)
        262144,// 25 (not square-free)
        524288,// 26 (not square-free)
        1048576,// 27 (not square-free)
        2097152,// 28 (not square-free)
        4194304,// 29
        8388608 // 30 (not square-free)
    ];
    const count = new Array(31).fill(0);
    for (const num of nums) {
        count[num]++;
    }
    const dp = new Array(1 << 10).fill(0);
    dp[0] = 1;
    for (let num = 2; num <= 30; num++) {
        const freq = count[num];
        if (freq === 0 || primeMasks[num] === 0) continue;
        for (let mask = (1 << 10) - 1; mask >= 0; mask--) {
            if ((mask & primeMasks[num]) === 0) {
                dp[mask | primeMasks[num]] = (dp[mask | primeMasks[num]] + dp[mask] * freq) % MOD;
            }
        }
    }
    let result = 0;
    for (let mask = 0; mask < (1 << 10); mask++) {
        result = (result + dp[mask]) % MOD;
    }
    const ones = count[1];
    for (let i = 0; i < ones; i++) {
        result = (result * 2) % MOD;
    }
    return (result - 1 + MOD) % MOD; // Subtract 1 to exclude the empty subset  
            
};
