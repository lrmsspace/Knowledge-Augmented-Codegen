// Source: https://leetcode.com/problems/sum-of-digit-differences-of-all-pairs/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums consisting of positive integers where all integers have the same number of digits.
//
// The digit difference between two integers is the count of different digits that are in the same position in the two integers.
//
// Return the sum of the digit differences between all pairs of integers in nums.
//
// Example:
// Input: nums = [13,23,12]
//
// Output: 4
//
// Explanation:
// We have the following:
// - The digit difference between 13 and 23 is 1.
// - The digit difference between 13 and 12 is 1.
// - The digit difference between 23 and 12 is 2.
// So the total sum of digit differences between all pairs of integers is 1 + 1 + 2 = 4.
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i] < 109
// 	All integers in nums have the same number of digits.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var sumDigitDifferences = function(nums) {
    const n = nums.length;
    const m = nums[0].toString().length;
    let totalDifference = 0;
    for (let i = 0; i < m; i++) {
        const count = Array(10).fill(0);
        for (const num of nums) {
            const digit = Math.floor(num / Math.pow(10, m - 1 - i)) % 10;
            count[digit]++;
        }
        for (let j = 0; j < 10; j++) {
            for (let k = j + 1; k < 10; k++) {
                totalDifference += count[j] * count[k];
            }
        }
    }
    return totalDifference * 2; 
};
