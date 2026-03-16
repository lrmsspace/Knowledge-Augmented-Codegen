// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-all-array-elements-equal-to-1/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums consisiting of positive integers. You can do the following operation on the array any number of times:
//
//
// 	Select an index i such that 0 <= i < n - 1 and replace either of nums[i] or nums[i+1] with their gcd value.
//
//
// Return the minimum number of operations to make all elements of nums equal to 1. If it is impossible, return -1.
//
// The gcd of two integers is the greatest common divisor of the two integers.
//
// Example:
// Input: nums = [2,6,3,4]
// Output: 4
// Explanation: We can do the following operations:
// - Choose index i = 2 and replace nums[2] with gcd(3,4) = 1. Now we have nums = [2,6,1,4].
// - Choose index i = 1 and replace nums[1] with gcd(6,1) = 1. Now we have nums = [2,1,1,4].
// - Choose index i = 0 and replace nums[0] with gcd(2,1) = 1. Now we have nums = [1,1,1,4].
// - Choose index i = 2 and replace nums[3] with gcd(1,4) = 1. Now we have nums = [1,1,1,1].
//
// Constraints:
// 2 <= nums.length <= 50
// 	1 <= nums[i] <= 106
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var minOperations = function(nums) {
    const n = nums.length;
    let onesCount = 0;
    for (const num of nums) {
        if (num === 1) {
            onesCount++;
        }
    }
    if (onesCount > 0) {
        return n - onesCount;
    }
    let minGcdSubarrayLength = Infinity;    
    for (let i = 0; i < n; i++) {
        let currentGcd = nums[i];
        for (let j = i + 1; j < n; j++) {
            currentGcd = gcd(currentGcd, nums[j]);
            if (currentGcd === 1) {
                minGcdSubarrayLength = Math.min(minGcdSubarrayLength, j - i + 1);
                break;
            }
        }   
    }                                               
    if (minGcdSubarrayLength === Infinity) {
        return -1;
    }
    return n - 1 + (minGcdSubarrayLength - 1);  
            
};
