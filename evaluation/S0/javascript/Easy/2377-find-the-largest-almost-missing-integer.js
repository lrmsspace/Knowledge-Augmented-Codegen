// Source: https://leetcode.com/problems/find-the-largest-almost-missing-integer/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums and an integer k.
//
// An integer x is almost missing from nums if x appears in exactly one subarray of size k within nums.
//
// Return the largest almost missing integer from nums. If no such integer exists, return -1.
// A subarray is a contiguous sequence of elements within an array.
//
// Example:
// Input: nums = [3,9,2,1,7], k = 3
//
// Output: 7
//
// Explanation:
//
//
// 	1 appears in 2 subarrays of size 3: [9, 2, 1] and [2, 1, 7].
// 	2 appears in 3 subarrays of size 3: [3, 9, 2], [9, 2, 1], [2, 1, 7].
// 	3 appears in 1 subarray of size 3: [3, 9, 2].
// 	7 appears in 1 subarray of size 3: [2, 1, 7].
// 	9 appears in 2 subarrays of size 3: [3, 9, 2], and [9, 2, 1].
//
//
// We return 7 since it is the largest integer that appears in exactly one subarray of size k.
//
// Constraints:
// 1 <= nums.length <= 50
// 	0 <= nums[i] <= 50
// 	1 <= k <= nums.length
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var largestInteger = function(nums, k) {
    const countMap = new Map();
    for (let i = 0; i <= nums.length - k; i++) {
        const subarray = nums.slice(i, i + k);
        const uniqueElements = new Set(subarray);
        for (const num of uniqueElements) {
            countMap.set(num, (countMap.get(num) || 0) + 1);
        }
    }
    let largestAlmostMissing = -1;
    for (const [num, count] of countMap.entries()) {
        if (count === 1 && num > largestAlmostMissing) {
            largestAlmostMissing = num;
        }
    }
    return largestAlmostMissing;    
};
