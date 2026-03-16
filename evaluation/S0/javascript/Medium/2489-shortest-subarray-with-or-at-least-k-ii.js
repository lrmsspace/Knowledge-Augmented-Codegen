// Source: https://leetcode.com/problems/shortest-subarray-with-or-at-least-k-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums of non-negative integers and an integer k.
//
// An array is called special if the bitwise OR of all of its elements is at least k.
//
// Return the length of the shortest special non-empty subarray of nums, or return -1 if no special subarray exists.
//
// Example:
// Input: nums = [1,2,3], k = 2
//
// Output: 1
//
// Explanation:
//
// The subarray [3] has OR value of 3. Hence, we return 1.
//
// Constraints:
// 1 <= nums.length <= 2 * 105
// 	0 <= nums[i] <= 109
// 	0 <= k <= 109
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var minimumSubarrayLength = function(nums, k) {
    const n = nums.length;
    let left = 0;
    let currentOR = 0;
    let minLength = Infinity;
    for (let right = 0; right < n; right++) {
        currentOR |= nums[right];
        while (left <= right && (currentOR & k) === k) {
            minLength = Math.min(minLength, right - left + 1);
            currentOR &= ~nums[left];
            left++;
        }
    }
    return minLength === Infinity ? -1 : minLength;
};