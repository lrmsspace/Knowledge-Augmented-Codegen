// Source: https://leetcode.com/problems/find-all-lonely-numbers-in-the-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. A number x is lonely when it appears only once, and no adjacent numbers (i.e. x + 1 and x - 1) appear in the array.
//
// Return all lonely numbers in nums. You may return the answer in any order.
//
// Example:
// Input: nums = [10,6,5,8]
// Output: [10,8]
// Explanation: 
// - 10 is a lonely number since it appears exactly once and 9 and 11 does not appear in nums.
// - 8 is a lonely number since it appears exactly once and 7 and 9 does not appear in nums.
// - 5 is not a lonely number since 6 appears in nums and vice versa.
// Hence, the lonely numbers in nums are [10, 8].
// Note that [8, 10] may also be returned.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 106
//

/**
 * @param {number[]} nums
 * @return {number[]}
 */
var findLonely = function(nums) {
    const numSet = new Set(nums);
    const lonelyNumbers = [];
    for (const num of nums) {
        if (
            nums.filter(x => x === num).length === 1 &&
            !numSet.has(num - 1) &&
            !numSet.has(num + 1)
        ) {
            lonelyNumbers.push(num);
        }
    }
    return lonelyNumbers;
};