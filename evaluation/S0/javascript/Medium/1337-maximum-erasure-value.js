// Source: https://leetcode.com/problems/maximum-erasure-value/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of positive integers nums and want to erase a subarray containing unique elements. The score you get by erasing the subarray is equal to the sum of its elements.
//
// Return the maximum score you can get by erasing exactly one subarray.
//
// An array b is called to be a subarray of a if it forms a contiguous subsequence of a, that is, if it is equal to a[l],a[l+1],...,a[r] for some (l,r).
//
// Example:
// Input: nums = [4,2,4,5,6]
// Output: 17
// Explanation: The optimal subarray here is [2,4,5,6].
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 104
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var maximumUniqueSubarray = function(nums) {
    const n = nums.length;
    const seen = new Set();
    let left = 0;
    let currentSum = 0;
    let maxSum = 0;
    for (let right = 0; right < n; right++) {
        while (seen.has(nums[right])) {
            seen.delete(nums[left]);
            currentSum -= nums[left];
            left++;
        }
        seen.add(nums[right]);
        currentSum += nums[right];
        maxSum = Math.max(maxSum, currentSum);
    }
    return maxSum;
};