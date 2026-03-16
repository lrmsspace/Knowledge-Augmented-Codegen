// Source: https://leetcode.com/problems/third-maximum-number/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums, return the third distinct maximum number in this array. If the third maximum does not exist, return the maximum number.
//
// Example:
// Input: nums = [3,2,1]
// Output: 1
// Explanation:
// The first distinct maximum is 3.
// The second distinct maximum is 2.
// The third distinct maximum is 1.
//
// Constraints:
// 1 <= nums.length <= 104
// 	-231 <= nums[i] <= 231 - 1
//
//
//  
// Follow up: Can you find an O(n) solution?
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var thirdMax = function(nums) {
    let first = -Infinity;
    let second = -Infinity;
    let third = -Infinity;
    for (const num of nums) {
        if (num === first || num === second || num === third) {
            continue;
        }
        if (num > first) {
            third = second;
            second = first;
            first = num;
        } else if (num > second) {
            third = second;
            second = num;
        } else if (num > third) {
            third = num;
        }
    }
    return third === -Infinity ? first : third;
};