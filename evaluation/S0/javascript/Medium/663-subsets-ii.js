// Source: https://leetcode.com/problems/subsets-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
//
// The solution set must not contain duplicate subsets. Return the solution in any order.
//
// Example:
// Input: nums = [1,2,2]
// Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
//
// Constraints:
// 1 <= nums.length <= 10
// 	-10 <= nums[i] <= 10
//

/**
 * @param {number[]} nums
 * @return {number[][]}
 */
var subsetsWithDup = function(nums) {
    nums.sort((a, b) => a - b); // Sort to handle duplicates
    const result = [];
    const subset = [];

    const backtrack = (start) => {
        result.push([...subset]);
        for (let i = start; i < nums.length; i++) {
            if (i > start && nums[i] === nums[i - 1]) continue; // Skip duplicates
            subset.push(nums[i]);
            backtrack(i + 1);
            subset.pop();
        }
    };

    backtrack(0);
    return result;
};