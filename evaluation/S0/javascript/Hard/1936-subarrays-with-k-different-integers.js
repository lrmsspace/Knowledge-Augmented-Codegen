// Source: https://leetcode.com/problems/subarrays-with-k-different-integers/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums and an integer k, return the number of good subarrays of nums.
//
// A good array is an array where the number of different integers in that array is exactly k.
//
//
// 	For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.
//
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [1,2,1,2,3], k = 2
// Output: 7
// Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2]
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= nums[i], k <= nums.length
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var subarraysWithKDistinct = function(nums, k) {
    const atMostK = (k) => {
        const count = new Map();
        let left = 0;
        let result = 0;
        for (let right = 0; right < nums.length; right++) {
            count.set(nums[right], (count.get(nums[right]) || 0) + 1);
            while (count.size > k) {
                count.set(nums[left], count.get(nums[left]) - 1);
                if (count.get(nums[left]) === 0) {
                    count.delete(nums[left]);
                }
                left++;
            }
            result += right - left + 1;
        }
        return result;
    };
    return atMostK(k) - atMostK(k - 1);
};
