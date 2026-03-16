// Source: https://leetcode.com/problems/count-elements-with-maximum-frequency/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array nums consisting of positive integers.
//
// Return the total frequencies of elements in nums such that those elements all have the maximum frequency.
//
// The frequency of an element is the number of occurrences of that element in the array.
//
// Example:
// Input: nums = [1,2,2,3,1,4]
// Output: 4
// Explanation: The elements 1 and 2 have a frequency of 2 which is the maximum frequency in the array.
// So the number of elements in the array with maximum frequency is 4.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 100
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var maxFrequencyElements = function(nums) {
    const frequencyMap = new Map();
    for (const num of nums) {
        frequencyMap.set(num, (frequencyMap.get(num) || 0) + 1);
    }
    let maxFrequency = 0;
    for (const freq of frequencyMap.values()) {
        if (freq > maxFrequency) {
            maxFrequency = freq;
        }
    }
    let count = 0;
    for (const [num, freq] of frequencyMap.entries()) {
        if (freq === maxFrequency) {
            count += freq;
        }
    }
    return count;
};