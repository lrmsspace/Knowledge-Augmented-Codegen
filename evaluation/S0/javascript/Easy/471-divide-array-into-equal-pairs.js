// Source: https://leetcode.com/problems/divide-array-into-equal-pairs/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums consisting of 2 * n integers.
//
// You need to divide nums into n pairs such that:
//
//
// 	Each element belongs to exactly one pair.
// 	The elements present in a pair are equal.
//
//
// Return true if nums can be divided into n pairs, otherwise return false.
//
// Example:
// Input: nums = [3,2,3,2,2,2]
// Output: true
// Explanation: 
// There are 6 elements in nums, so they should be divided into 6 / 2 = 3 pairs.
// If nums is divided into the pairs (2, 2), (3, 3), and (2, 2), it will satisfy all the conditions.
//
// Constraints:
// nums.length == 2 * n
// 	1 <= n <= 500
// 	1 <= nums[i] <= 500
//

/**
 * @param {number[]} nums
 * @return {boolean}
 */
var divideArray = function(nums) {
    const countMap = new Map();
    for (const num of nums) {
        countMap.set(num, (countMap.get(num) || 0) + 1);
    }
    for (const count of countMap.values()) {
        if (count % 2 !== 0) {
            return false;
        }
    }
    return true;
};