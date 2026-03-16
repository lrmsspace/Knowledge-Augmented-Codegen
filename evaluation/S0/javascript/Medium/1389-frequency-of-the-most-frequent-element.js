// Source: https://leetcode.com/problems/frequency-of-the-most-frequent-element/   |   Difficulty: Medium
//
// Problem Description:
// The frequency of an element is the number of times it occurs in an array.
//
// You are given an integer array nums and an integer k. In one operation, you can choose an index of nums and increment the element at that index by 1.
//
// Return the maximum possible frequency of an element after performing at most k operations.
//
// Example:
// Input: nums = [1,2,4], k = 5
// Output: 3
// Explanation: Increment the first element three times and the second element two times to make nums = [4,4,4].
// 4 has a frequency of 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
// 	1 <= k <= 105
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var maxFrequency = function(nums, k) {
    nums.sort((a, b) => a - b);
    let left = 0;
    let total = 0;
    let maxFreq = 1;
    for (let right = 0; right < nums.length; right++) {
        total += nums[right];
        while ((right - left + 1) * nums[right] - total > k) {
            total -= nums[left];
            left++;
        }
        maxFreq = Math.max(maxFreq, right - left + 1);
    }
    return maxFreq;
};