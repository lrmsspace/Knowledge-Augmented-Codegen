// Source: https://leetcode.com/problems/number-of-good-pairs/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of integers nums, return the number of good pairs.
//
// A pair (i, j) is called good if nums[i] == nums[j] and i < j.
//
// Example:
// Input: nums = [1,2,3,1,1,3]
// Output: 4
// Explanation: There are 4 good pairs (0,3), (0,4), (3,4), (2,5) 0-indexed.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 100
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var numIdenticalPairs = function(nums) {
    const countMap = {};
    let goodPairsCount = 0;
    for (const num of nums) {
        if (countMap[num]) {
            goodPairsCount += countMap[num];
            countMap[num]++;
        } else {
            countMap[num] = 1;
        }
    }
    return goodPairsCount;
};