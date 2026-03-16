// Source: https://leetcode.com/problems/find-k-th-smallest-pair-distance/   |   Difficulty: Hard
//
// Problem Description:
// The distance of a pair of integers a and b is defined as the absolute difference between a and b.
//
// Given an integer array nums and an integer k, return the kth smallest distance among all the pairs nums[i] and nums[j] where 0 <= i < j < nums.length.
//
// Example:
// Input: nums = [1,3,1], k = 1
// Output: 0
// Explanation: Here are all the pairs:
// (1,3) -> 2
// (1,1) -> 0
// (3,1) -> 2
// Then the 1st smallest distance pair is (1,1), and its distance is 0.
//
// Constraints:
// n == nums.length
// 	2 <= n <= 104
// 	0 <= nums[i] <= 106
// 	1 <= k <= n * (n - 1) / 2
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var smallestDistancePair = function(nums, k) {
    


    let left = 0;
    let right = 1000000;
    while (left < right) {
        const mid = Math.floor((left + right) / 2);
        let count = 0;
        for (let i = 0; i < nums.length; i++) {
            for (let j = i + 1; j < nums.length; j++) {
                if (Math.abs(nums[i] - nums[j]) <= mid) {
                    count++;
                }
            }
        }
        if (count < k) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
    
};
