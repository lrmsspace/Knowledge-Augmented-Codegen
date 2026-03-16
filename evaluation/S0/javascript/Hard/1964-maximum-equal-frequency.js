// Source: https://leetcode.com/problems/maximum-equal-frequency/   |   Difficulty: Hard
//
// Problem Description:
// Given an array nums of positive integers, return the longest possible length of an array prefix of nums, such that it is possible to remove exactly one element from this prefix so that every number that has appeared in it will have the same number of occurrences.
//
// If after removing one element there are no remaining elements, it's still considered that every appeared number has the same number of ocurrences (0).
//
// Example:
// Input: nums = [2,2,1,1,5,3,3,5]
// Output: 7
// Explanation: For the subarray [2,2,1,1,5,3,3] of length 7, if we remove nums[4] = 5, we will get [2,2,1,1,3,3], so that each number will appear exactly twice.
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var maxEqualFreq = function(nums) {
    const count = new Map();
    const freq = new Map();
    let maxLength = 0;
    for (let i = 0; i < nums.length; i++) {
        const num = nums[i];
        const prevCount = count.get(num) || 0;
        if (prevCount > 0) {
            freq.set(prevCount, (freq.get(prevCount) || 0) - 1);
        }
        const newCount = prevCount + 1;
        count.set(num, newCount);
        freq.set(newCount, (freq.get(newCount) || 0) + 1);
        if (freq.size === 1) {
            const [key, value] = freq.entries().next().value;
            if (key === 1 || value === 1) {
                maxLength = i + 1;
            }
        } else if (freq.size === 2) {
            const entries = Array.from(freq.entries());
            const [key1, value1] = entries[0];
            const [key2, value2] = entries[1];
            if ((key1 === 1 && value1 === 1) || (key2 === 1 && value2 === 1) || (Math.abs(key1 - key2) === 1 && ((key1 > key2 && value1 === 1) || (key2 > key1 && value2 === 1)))) {
                maxLength = i + 1;
            }
        }
    }
    return maxLength;   
};
