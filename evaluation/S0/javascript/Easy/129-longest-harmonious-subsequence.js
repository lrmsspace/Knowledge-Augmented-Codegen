// Source: https://leetcode.com/problems/longest-harmonious-subsequence/   |   Difficulty: Easy
//
// Problem Description:
// We define a harmonious array as an array where the difference between its maximum value and its minimum value is exactly 1.
//
// Given an integer array nums, return the length of its longest harmonious subsequence among all its possible subsequences.
//
// Example:
// Input: nums = [1,3,2,2,5,2,3,7]
//
// Output: 5
//
// Explanation:
//
// The longest harmonious subsequence is [3,2,2,2,3].
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	-109 <= nums[i] <= 109
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var findLHS = function(nums) {
    const numCounts = new Map();

    // Count the occurrences of each number in the array
    for (const num of nums) {
        numCounts.set(num, (numCounts.get(num) || 0) + 1);
    }
    let maxLength = 0;

    // Iterate through the unique numbers and check for harmonious subsequences
    for (const [num, count] of numCounts.entries()) {
        if (numCounts.has(num + 1)) {
            const currentLength = count + numCounts.get(num + 1);
            maxLength = Math.max(maxLength, currentLength);
        }
    }
    return maxLength;           
};
