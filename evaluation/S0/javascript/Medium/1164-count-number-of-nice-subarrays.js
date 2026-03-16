// Source: https://leetcode.com/problems/count-number-of-nice-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and an integer k. A continuous subarray is called nice if there are k odd numbers on it.
//
// Return the number of nice sub-arrays.
//
// Example:
// Input: nums = [1,1,2,1,1], k = 3
// Output: 2
// Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].
//
// Constraints:
// 1 <= nums.length <= 50000
// 	1 <= nums[i] <= 10^5
// 	1 <= k <= nums.length
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var numberOfSubarrays = function(nums, k) {
    
    let oddIndices = [-1];
    let niceSubarraysCount = 0;
    const n = nums.length;

    for (let i = 0; i < n; i++) {
        if (nums[i] % 2 === 1) {
            oddIndices.push(i);
        }
    }
    oddIndices.push(n); 
    const oddCount = oddIndices.length; 
    for (let i = 1; i + k < oddCount; i++) {
        const leftEvenCount = oddIndices[i] - oddIndices[i - 1];
        const rightEvenCount = oddIndices[i + k] - oddIndices[i + k - 1];
        niceSubarraysCount += leftEvenCount * rightEvenCount;
    }   

    return niceSubarraysCount;  
    
};
