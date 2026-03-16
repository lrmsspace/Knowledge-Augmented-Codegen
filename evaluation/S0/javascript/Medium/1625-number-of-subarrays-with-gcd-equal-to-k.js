// Source: https://leetcode.com/problems/number-of-subarrays-with-gcd-equal-to-k/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and an integer k, return the number of subarrays of nums where the greatest common divisor of the subarray's elements is k.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// The greatest common divisor of an array is the largest integer that evenly divides all the array elements.
//
// Example:
// Input: nums = [9,3,1,2,6,3], k = 3
// Output: 4
// Explanation: The subarrays of nums where 3 is the greatest common divisor of all the subarray's elements are:
// - [9,3,1,2,6,3]
// - [9,3,1,2,6,3]
// - [9,3,1,2,6,3]
// - [9,3,1,2,6,3]
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i], k <= 109
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var subarrayGCD = function(nums, k) {
    const gcd = (a, b) => {
        while (b !== 0) {
            const temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    };
    let count = 0;
    const n = nums.length;
    for (let i = 0; i < n; i++) {
        let currentGCD = 0;
        for (let j = i; j < n; j++) {
            currentGCD = gcd(currentGCD, nums[j]);
            if (currentGCD === k) {
                count++;
            }
            if (currentGCD < k) {
                break;
            }
        }
    }
    return count;
}   ;
