// Source: https://leetcode.com/problems/n-repeated-element-in-size-2n-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums with the following properties:
//
//
// 	nums.length == 2 * n.
// 	nums contains n + 1 unique elements.
// 	Exactly one element of nums is repeated n times.
//
//
// Return the element that is repeated n times.
//
// Example:
// Input: nums = [1,2,3,3]
// Output: 3
//
// Constraints:
// 2 <= n <= 5000
// 	nums.length == 2 * n
// 	0 <= nums[i] <= 104
// 	nums contains n + 1 unique elements and one of them is repeated exactly n times.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var repeatedNTimes = function(nums) {
    const seen = new Set();
    for (const num of nums) {
        if (seen.has(num)) {
            return num;
        }
        seen.add(num);
    }
    return -1; // This line should never be reached given the problem constraints
};
