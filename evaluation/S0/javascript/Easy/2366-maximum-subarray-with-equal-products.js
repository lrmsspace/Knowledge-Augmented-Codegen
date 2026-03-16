// Source: https://leetcode.com/problems/maximum-subarray-with-equal-products/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of positive integers nums.
//
// An array arr is called product equivalent if prod(arr) == lcm(arr) * gcd(arr), where:
//
//
// 	prod(arr) is the product of all elements of arr.
// 	gcd(arr) is the GCD of all elements of arr.
// 	lcm(arr) is the LCM of all elements of arr.
//
//
// Return the length of the longest product equivalent subarray of nums.
//
// Example:
// Input: nums = [1,2,1,2,1,1,1]
//
// Output: 5
//
// Explanation: 
//
// The longest product equivalent subarray is [1, 2, 1, 1, 1], where prod([1, 2, 1, 1, 1]) = 2, gcd([1, 2, 1, 1, 1]) = 1, and lcm([1, 2, 1, 1, 1]) = 2.
//
// Constraints:
// 2 <= nums.length <= 100
// 	1 <= nums[i] <= 10
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var maxLength = function(nums) {
    let maxLen = 1;
    const n = nums.length;
    for (let i = 0; i < n; i++) {
        let prod = 1;
        let gcd = nums[i];
        let lcm = nums[i];
        for (let j = i; j < n; j++) {   
            prod *= nums[j];
            gcd = computeGCD(gcd, nums[j]);
            lcm = computeLCM(lcm, nums[j]);
            if (prod === gcd * lcm) {
                maxLen = Math.max(maxLen, j - i + 1);
            }
        }
    }
    return maxLen;  
};
