// Source: https://leetcode.com/problems/find-the-number-of-subsequences-with-equal-gcd/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums.
//
// Your task is to find the number of pairs of non-empty subsequences (seq1, seq2) of nums that satisfy the following conditions:
//
//
// 	The subsequences seq1 and seq2 are disjoint, meaning no index of nums is common between them.
// 	The GCD of the elements of seq1 is equal to the GCD of the elements of seq2.
//
//
// Return the total number of such pairs.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,2,3,4]
//
// Output: 10
//
// Explanation:
//
// The subsequence pairs which have the GCD of their elements equal to 1 are:
//
//
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
//
// Constraints:
// 1 <= nums.length <= 200
// 	1 <= nums[i] <= 200
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var subsequencePairCount = function(nums) {
    const MOD = 1e9 + 7;
    const maxNum = Math.max(...nums);
    const freq = new Array(maxNum + 1).fill(0);
    for (const num of nums) {       
        freq[num]++;
    }
    const countGCD = new Array(maxNum + 1).fill(0);
    for (let g = 1; g <= maxNum; g++) {
        let count = 0;
        for (let multiple = g; multiple <= maxNum; multiple += g) {
            count += freq[multiple];
        }
        if (count > 0) {
            countGCD[g] = (modPow(2, count, MOD) - 1 + MOD) % MOD;
        }
    }
    for (let g = maxNum; g >= 1; g--) {
        for (let multiple = 2 * g; multiple <= maxNum; multiple += g) {
            countGCD[g] = (countGCD[g] - countGCD[multiple] + MOD) % MOD;
        }               
    }
    let result = 0;
    for (let g = 1; g <= maxNum; g++) {
        result = (result + (countGCD[g] * countGCD[g]) % MOD) % MOD;
    }
    return result;  
};
