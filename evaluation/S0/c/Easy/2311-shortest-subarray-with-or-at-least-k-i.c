// Source: https://leetcode.com/problems/shortest-subarray-with-or-at-least-k-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array nums of non-negative integers and an integer k.
//
// An array is called special if the bitwise OR of all of its elements is at least k.
//
// Return the length of the shortest special non-empty subarray of nums, or return -1 if no special subarray exists.
//
// Example:
// Input: nums = [1,2,3], k = 2
//
// Output: 1
//
// Explanation:
//
// The subarray [3] has OR value of 3. Hence, we return 1.
//
// Note that [2] is also a special subarray.
//
// Constraints:
// 1 <= nums.length <= 50
// 	0 <= nums[i] <= 50
// 	0 <= k < 64
//

int minimumSubarrayLength(int* nums, int numsSize, int k) {
    for (int length = 1; length <= numsSize; length++) {
        for (int start = 0; start <= numsSize - length; start++) {
            int orValue = 0;
            for (int i = start; i < start + length; i++) {
                orValue |= nums[i];
            }
            if (orValue >= k) {
                return length;
            }
        }
    }
    return -1;      
}
