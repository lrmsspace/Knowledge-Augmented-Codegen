// Source: https://leetcode.com/problems/sliding-subarray-beauty/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums containing n integers, find the beauty of each subarray of size k.
//
// The beauty of a subarray is the xth smallest integer in the subarray if it is negative, or 0 if there are fewer than x negative integers.
//
// Return an integer array containing n - k + 1 integers, which denote the beauty of the subarrays in order from the first index in the array.
//
//
// 	
// 	A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,-1,-3,-2,3], k = 3, x = 2
// Output: [-1,-2,-2]
// Explanation: There are 3 subarrays with size k = 3. 
// The first subarray is [1, -1, -3] and the 2nd smallest negative integer is -1. 
// The second subarray is [-1, -3, -2] and the 2nd smallest negative integer is -2. 
// The third subarray is [-3, -2, 3] and the 2nd smallest negative integer is -2.
//
// Constraints:
// n == nums.length 
// 	1 <= n <= 105
// 	1 <= k <= n
// 	1 <= x <= k 
// 	-50 <= nums[i] <= 50
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @param {number} x
 * @return {number[]}
 */
var getSubarrayBeauty = function(nums, k, x) {
    const result = [];
    const count = new Array(51).fill(0); // Count array for numbers from -50 to 0
    const offset = 50; // Offset to handle negative indices
    let negativeCount = 0;
        
    for (let i = 0; i < nums.length; i++) {
        if (nums[i] < 0) {
            count[nums[i] + offset]++;
            negativeCount++;
        }
        if (i >= k) {
            if (nums[i - k] < 0) {
                count[nums[i - k] + offset]--;
                negativeCount--;
            }
        }



        if (i >= k - 1) {
            if (negativeCount < x) {
                result.push(0);
            } else {
                let cumulativeCount = 0;
                for (let j = 0; j < 51; j++) {
                    cumulativeCount += count[j];
                    if (cumulativeCount >= x) {
                        result.push(j - offset);
                        break;
                    }
                }
            }
        }
    }
    return result;  
                    
};
