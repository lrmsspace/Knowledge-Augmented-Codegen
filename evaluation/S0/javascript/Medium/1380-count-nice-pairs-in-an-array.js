// Source: https://leetcode.com/problems/count-nice-pairs-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums that consists of non-negative integers. Let us define rev(x) as the reverse of the non-negative integer x. For example, rev(123) = 321, and rev(120) = 21. A pair of indices (i, j) is nice if it satisfies all of the following conditions:
//
//
// 	0 <= i < j < nums.length
// 	nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])
//
//
// Return the number of nice pairs of indices. Since that number can be too large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [42,11,1,97]
// Output: 2
// Explanation: The two pairs are:
//  - (0,3) : 42 + rev(97) = 42 + 79 = 121, 97 + rev(42) = 97 + 24 = 121.
//  - (1,2) : 11 + rev(1) = 11 + 1 = 12, 1 + rev(11) = 1 + 11 = 12.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var countNicePairs = function(nums) {
    const MOD = 1e9 + 7;
    const freqMap = new Map();
    let nicePairsCount = 0;

    const reverseNumber = (num) => {
        let reversed = 0;
        while (num > 0) {
            reversed = reversed * 10 + (num % 10);
            num = Math.floor(num / 10);
        }
        return reversed;
    };

    for (const num of nums) {
        const diff = num - reverseNumber(num);
        const count = freqMap.get(diff) || 0;
        nicePairsCount = (nicePairsCount + count) % MOD;
        freqMap.set(diff, count + 1);
    }

    return nicePairsCount;
};