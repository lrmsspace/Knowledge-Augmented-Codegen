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

            // Check if the mid index is even or odd
            boolean isEven = (mid % 2 == 0);

            // Check if the mid element is equal to the next element
            if (nums[mid] == nums[mid + 1]) {
                // If mid is even, the single element is in the right half
                // If mid is odd, the single element is in the left half
                if (isEven) {
                    left = mid + 2; // Move past the pair
                } else {
                    right = mid - 1; // Move before the pair
                }
            } else {
                // Check if the mid element is equal to the previous element
                if (mid > 0 && nums[mid] == nums[mid - 1]) {
                    // If mid is even, the single element is in the left half
                    // If mid is odd, the single element is in the right half
                    if (isEven) {
                        right = mid - 2; // Move before the pair
                    } else {
                        left = mid + 1; // Move past the pair
                    }
                } else {
                    // If mid element does not match either neighbor, it must be the single element
                    return nums[mid];
                }
            }
        }

        // When left meets right, it will be the single element
        return nums[left];          
    }
}
