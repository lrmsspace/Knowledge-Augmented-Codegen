// Source: https://leetcode.com/problems/find-the-power-of-k-size-subarrays-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers nums of length n and a positive integer k.
//
// The power of an array is defined as:
//
//
// 	Its maximum element if all of its elements are consecutive and sorted in ascending order.
// 	-1 otherwise.
//
//
// You need to find the power of all subarrays of nums of size k.
//
// Return an integer array results of size n - k + 1, where results[i] is the power of nums[i..(i + k - 1)].
//
// Example:
// Input: nums = [1,2,3,4,3,2,5], k = 3
//
// Output: [3,4,-1,-1,-1]
//
// Explanation:
//
// There are 5 subarrays of nums of size 3:
//
//
// 	[1, 2, 3] with the maximum element 3.
// 	[2, 3, 4] with the maximum element 4.
// 	[3, 4, 3] whose elements are not consecutive.
// 	[4, 3, 2] whose elements are not sorted.
// 	[3, 2, 5] whose elements are not consecutive.
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	1 <= nums[i] <= 106
// 	1 <= k <= n
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number[]}
 */
var resultsArray = function(nums, k) {
    const results = [];
    for (let i = 0; i <= nums.length - k; i++) {
        const subarray = nums.slice(i, i + k);
        const maxElement = Math.max(...subarray);
        const minElement = Math.min(...subarray);
        if (maxElement - minElement === k - 1 && new Set(subarray).size === k) {
            results.push(maxElement);
        } else {
            results.push(-1);
        }
    }
    return results;
};
