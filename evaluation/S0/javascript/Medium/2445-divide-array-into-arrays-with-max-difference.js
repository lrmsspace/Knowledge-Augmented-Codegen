// Source: https://leetcode.com/problems/divide-array-into-arrays-with-max-difference/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of size n where n is a multiple of 3 and a positive integer k.
//
// Divide the array nums into n / 3 arrays of size 3 satisfying the following condition:
//
//
// 	The difference between any two elements in one array is less than or equal to k.
//
//
// Return a 2D array containing the arrays. If it is impossible to satisfy the conditions, return an empty array. And if there are multiple answers, return any of them.
//
// Example:
// Input: nums = [1,3,4,8,7,9,3,5,1], k = 2
//
// Output: [[1,1,3],[3,4,5],[7,8,9]]
//
// Explanation:
//
// The difference between any two elements in each array is less than or equal to 2.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	n is a multiple of 3
// 	1 <= nums[i] <= 105
// 	1 <= k <= 105
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number[][]}
 */
var divideArray = function(nums, k) {
    nums.sort((a, b) => a - b);     
    const result = [];
    for (let i = 0; i < nums.length; i += 3) {
        if (nums[i + 2] - nums[i] > k) {
            return [];
        }
        result.push([nums[i], nums[i + 1], nums[i + 2]]);
    }
    return result;
};