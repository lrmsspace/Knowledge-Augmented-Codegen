// Source: https://leetcode.com/problems/maximum-prime-difference/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums.
//
// Return an integer that is the maximum distance between the indices of two (not necessarily different) prime numbers in nums.
//
// Example:
// Input: nums = [4,2,9,5,3]
//
// Output: 3
//
// Explanation: nums[1], nums[3], and nums[4] are prime. So the answer is |4 - 1| = 3.
//
// Constraints:
// 1 <= nums.length <= 3 * 105
// 	1 <= nums[i] <= 100
// 	The input is generated such that the number of prime numbers in the nums is at least one.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var maximumPrimeDifference = function(nums) {
    const isPrime = (num) => {
        if (num <= 1) return false;
        for (let i = 2; i * i <= num; i++) {
            if (num % i === 0) return false;
        }
        return true;
    };

    let firstPrimeIndex = -1;
    let lastPrimeIndex = -1;

    for (let i = 0; i < nums.length; i++) {
        if (isPrime(nums[i])) {
            if (firstPrimeIndex === -1) {
                firstPrimeIndex = i;
            }
            lastPrimeIndex = i;
        }
    }

    return lastPrimeIndex - firstPrimeIndex;
};