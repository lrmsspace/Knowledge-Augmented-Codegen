// Source: https://leetcode.com/problems/maximum-and-minimum-sums-of-at-most-size-k-subsequences/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and a positive integer k. Return the sum of the maximum and minimum elements of all subsequences of nums with at most k elements.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,2,3], k = 2
//
// Output: 24
//
// Explanation:
//
// The subsequences of nums with at most 2 elements are:
//
//
// 	
// 		
// 			Subsequence 
// 			Minimum
// 			Maximum
// 			Sum
// 		
// 		
// 			[1]
// 			1
// 			1
// 			2
// 		
// 		
// 			[2]
// 			2
// 			2
// 			4
// 		
// 		
// 			[3]
// 			3
// 			3
// 			6
// 		
// 		
// 			[1, 2]
// 			1
// 			2
// 			3
// 		
// 		
// 			[1, 3]
// 			1
// 			3
// 			4
// 		
// 		
// 			[2, 3]
// 			2
// 			3
// 			5
// 		
// 		
// 			Final Total
// 			 
// 			 
// 			24
// 		
// 	
//
//
// The output would be 24.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
// 	1 <= k <= min(70, nums.length)
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var minMaxSums = function(nums, k) {
    const mod = 1e9 + 7;
    const n = nums.length;
    nums.sort((a, b) => a - b);
    let totalSum = 0;
    for (let i = 0; i < n; i++) {
        const maxCount = Math.min(k - 1, n - 1 - i);
        const minCount = Math.min(k - 1, i);
        totalSum = (totalSum + nums[i] * (maxCount + 1) + nums[i] * (minCount + 1)) % mod;
    }
    return totalSum;    
};
