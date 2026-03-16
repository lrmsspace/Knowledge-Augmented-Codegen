// Source: https://leetcode.com/problems/maximum-and-minimum-sums-of-at-most-size-k-subarrays/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and a positive integer k. Return the sum of the maximum and minimum elements of all subarrays with at most k elements.
//
// Example:
// Input: nums = [1,2,3], k = 2
//
// Output: 20
//
// Explanation:
//
// The subarrays of nums with at most 2 elements are:
//
//
// 	
// 		
// 			Subarray
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
// 			[2, 3]
// 			2
// 			3
// 			5
// 		
// 		
// 			Final Total
// 			 
// 			 
// 			20
// 		
// 	
//
//
// The output would be 20.
//
// Constraints:
// 1 <= nums.length <= 80000
// 	1 <= k <= nums.length
// 	-106 <= nums[i] <= 106
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var minMaxSubarraySum = function(nums, k) {
    const n = nums.length;
    let totalSum = 0;
    const mod = 1e9 + 7;

    // Helper function to calculate sum of minimums
    const sumOfMinimums = () => {
        const stack = [];
        const left = Array(n).fill(-1);
        const right = Array(n).fill(n);
        for (let i = 0; i < n; i++) {
            while (stack.length && nums[stack[stack.length - 1]] > nums[i]) {
                right[stack.pop()] = i;
            }
            stack.push(i);
        }
        stack.length = 0;
        for (let i = n - 1; i >= 0; i--) {
            while (stack.length && nums[stack[stack.length - 1]] >= nums[i]) {
                left[stack.pop()] = i;
            }
            stack.push(i);
        }   
        let sumMin = 0;
        for (let i = 0; i < n; i++) {
            const count = (i - left[i]) * (right[i] - i);
            const validCount = Math.min(count, k * (k + 1) / 2);
            sumMin = (sumMin + nums[i] * validCount) % mod;
        }
        return sumMin;
    };
};
