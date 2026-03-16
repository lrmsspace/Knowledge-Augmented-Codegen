// Source: https://leetcode.com/problems/number-of-pairs-of-strings-with-concatenation-equal-to-target/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of digit strings nums and a digit string target, return the number of pairs of indices (i, j) (where i != j) such that the concatenation of nums[i] + nums[j] equals target.
//
// Example:
// Input: nums = ["777","7","77","77"], target = "7777"
// Output: 4
// Explanation: Valid pairs are:
// - (0, 1): "777" + "7"
// - (1, 0): "7" + "777"
// - (2, 3): "77" + "77"
// - (3, 2): "77" + "77"
//
// Constraints:
// 2 <= nums.length <= 100
// 	1 <= nums[i].length <= 100
// 	2 <= target.length <= 100
// 	nums[i] and target consist of digits.
// 	nums[i] and target do not have leading zeros.
//

/**
 * @param {string[]} nums
 * @param {string} target
 * @return {number}
 */
var numOfPairs = function(nums, target) {
    let count = 0;    
    const n = nums.length;

    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            if (i !== j && nums[i] + nums[j] === target) {
                count++;
            }
        }
    }
    return count;   
};
