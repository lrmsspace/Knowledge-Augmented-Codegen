// Source: https://leetcode.com/problems/minimum-size-subarray-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of positive integers nums and a positive integer target, return the minimal length of a subarray whose sum is greater than or equal to target. If there is no such subarray, return 0 instead.
//
// Example:
// Input: target = 7, nums = [2,3,1,2,4,3]
// Output: 2
// Explanation: The subarray [4,3] has the minimal length under the problem constraint.
//
// Constraints:
// 1 <= target <= 109
// 	1 <= nums.length <= 105
// 	1 <= nums[i] <= 104
//
//
//  
// Follow up: If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log(n)).
//

/**
 * @param {number} target
 * @param {number[]} nums
 * @return {number}
 */
var minSubArrayLen = function(target, nums) {
    let left = 0;
    let sum = 0;
    let minLength = Infinity;

    for (let right = 0; right < nums.length; right++) {
        sum += nums[right];

        while (sum >= target) {
            minLength = Math.min(minLength, right - left + 1);
            sum -= nums[left];
            left++;
        }
    }

    return minLength === Infinity ? 0 : minLength;
};