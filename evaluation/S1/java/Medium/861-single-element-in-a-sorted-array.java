// Source: https://leetcode.com/problems/single-element-in-a-sorted-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a sorted array consisting of only integers where every element appears exactly twice, except for one element which appears exactly once.
//
// Return the single element that appears only once.
//
// Your solution must run in O(log n) time and O(1) space.
//
// Example:
// Input: nums = [1,1,2,3,3,4,4,8,8]
// Output: 2
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 105
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int singleNonDuplicate(int[] nums) {
        int left = 0;
        int right = nums.length - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            // Ensure mid is even for comparison
            if (mid % 2 == 1) {
                mid--;
            }

            // Check if the pair is valid
            if (nums[mid] == nums[mid + 1]) {
                // Single element is in the right half
                left = mid + 2;
            } else {
                // Single element is in the left half
                right = mid;
            }
        }

        return nums[left];          
    }
}
