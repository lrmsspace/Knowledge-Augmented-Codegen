// Source: https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and an integer limit, return the size of the longest non-empty subarray such that the absolute difference between any two elements of this subarray is less than or equal to limit.
//
// Example:
// Input: nums = [8,2,4,7], limit = 4
// Output: 2 
// Explanation: All subarrays are: 
// [8] with maximum absolute diff |8-8| = 0 <= 4.
// [8,2] with maximum absolute diff |8-2| = 6 > 4. 
// [8,2,4] with maximum absolute diff |8-2| = 6 > 4.
// [8,2,4,7] with maximum absolute diff |8-2| = 6 > 4.
// [2] with maximum absolute diff |2-2| = 0 <= 4.
// [2,4] with maximum absolute diff |2-4| = 2 <= 4.
// [2,4,7] with maximum absolute diff |2-7| = 5 > 4.
// [4] with maximum absolute diff |4-4| = 0 <= 4.
// [4,7] with maximum absolute diff |4-7| = 3 <= 4.
// [7] with maximum absolute diff |7-7| = 0 <= 4. 
// Therefore, the size of the longest subarray is 2.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	0 <= limit <= 109
//

/**
 * @param {number[]} nums
 * @param {number} limit
 * @return {number}
 */
var longestSubarray = function(nums, limit) {
    let maxDeque = [];
    let minDeque = [];
    let left = 0;
    let result = 0;
    for (let right = 0; right < nums.length; right++) {
        while (maxDeque.length && nums[right] > maxDeque[maxDeque.length - 1]) {
            maxDeque.pop();
        }
        maxDeque.push(nums[right]);
        while (minDeque.length && nums[right] < minDeque[minDeque.length - 1]) {
            minDeque.pop();
        }
        minDeque.push(nums[right]);
        while (maxDeque[0] - minDeque[0] > limit) {
            if (nums[left] === maxDeque[0]) {
                maxDeque.shift();
            }
            if (nums[left] === minDeque[0]) {
                minDeque.shift();
            }
            left++;
        }
        result = Math.max(result, right - left + 1);
    }
    return result;
        
};
