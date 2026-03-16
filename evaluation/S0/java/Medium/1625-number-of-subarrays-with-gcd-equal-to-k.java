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

class Solution {
    public int subarrayGCD(int[] nums, int k) {
        int count = 0;
        for (int i = 0; i < nums.length; i++) {
            int currentGCD = 0;
            for (int j = i; j < nums.length; j++) {
                currentGCD = gcd(currentGCD, nums[j]);
                if (currentGCD == k) {
                    count++;
                } else if (currentGCD < k) {
                    break;
                }
            }
        }
        return count;           
    }
}
