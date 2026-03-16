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

class Solution {
    public int maxLength(int[] nums) {
        int maxLength = 0;
        int n = nums.length;

        for (int i = 0; i < n; i++) {
            int prod = 1;
            int gcd = nums[i];
            int lcm = nums[i];

            for (int j = i; j < n; j++) {
                prod *= nums[j];
                gcd = computeGCD(gcd, nums[j]);
                lcm = computeLCM(lcm, nums[j]);

                if (prod == gcd * lcm) {
                    maxLength = Math.max(maxLength, j - i + 1);
                }
            }
        }

        return maxLength;           
    }
}
