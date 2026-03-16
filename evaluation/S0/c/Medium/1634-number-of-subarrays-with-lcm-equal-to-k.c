// Source: https://leetcode.com/problems/number-of-subarrays-with-lcm-equal-to-k/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and an integer k, return the number of subarrays of nums where the least common multiple of the subarray's elements is k.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// The least common multiple of an array is the smallest positive integer that is divisible by all the array elements.
//
// Example:
// Input: nums = [3,6,2,7,1], k = 6
// Output: 4
// Explanation: The subarrays of nums where 6 is the least common multiple of all the subarray's elements are:
// - [3,6,2,7,1]
// - [3,6,2,7,1]
// - [3,6,2,7,1]
// - [3,6,2,7,1]
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i], k <= 1000
//

int subarrayLCM(int* nums, int numsSize, int k) {
    int count = 0;

    for (int start = 0; start < numsSize; start++) {
        int lcm = 1;

        for (int end = start; end < numsSize; end++) {
            int num = nums[end];

            // Calculate LCM using GCD
            int gcd = 1;
            for (int i = 1; i <= lcm && i <= num; i++) {
                if (lcm % i == 0 && num % i == 0) {
                    gcd = i;
                }
            }
            lcm = (lcm * num) / gcd;

            if (lcm > k) {
                break; // No need to continue if LCM exceeds k
            }
            if (lcm == k) {
                count++;
            }
        }
    }

    return count;       
}
