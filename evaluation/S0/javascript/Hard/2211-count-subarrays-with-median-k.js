// Source: https://leetcode.com/problems/count-subarrays-with-median-k/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums of size n consisting of distinct integers from 1 to n and a positive integer k.
//
// Return the number of non-empty subarrays in nums that have a median equal to k.
//
// Note:
//
//
// 	The median of an array is the middle element after sorting the array in ascending order. If the array is of even length, the median is the left middle element.
//
// 	
// 		For example, the median of [2,3,1,4] is 2, and the median of [8,4,3,5,1] is 4.
// 	
// 	
// 	A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [3,2,1,4,5], k = 4
// Output: 3
// Explanation: The subarrays that have a median equal to 4 are: [4], [4,5] and [1,4,5].
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	1 <= nums[i], k <= n
// 	The integers in nums are distinct.
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var countSubarrays = function(nums, k) {
    const n = nums.length;
    const index = nums.indexOf(k);
    const countMap = new Map();
    countMap.set(0, 1);
    let count = 0;
    let balance = 0;
    for (let i = index + 1; i < n; i++) {
        balance += nums[i] > k ? 1 : -1;
        count += countMap.get(balance) || 0;
    }
    balance = 0;
    for (let i = index - 1; i >= 0; i--) {
        balance += nums[i] < k ? 1 : -1;
        count += countMap.get(-balance) || 0;
        countMap.set(balance, (countMap.get(balance) || 0) + 1);
    }
    return count;
};
