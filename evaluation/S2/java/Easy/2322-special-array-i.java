// Source: https://leetcode.com/problems/special-array-i/   |   Difficulty: Easy
//
// Problem Description:
// An array is considered special if the parity of every pair of adjacent elements is different. In other words, one element in each pair must be even, and the other must be odd.
//
// You are given an array of integers nums. Return true if nums is a special array, otherwise, return false.
//
// Example:
// Input: nums = [1]
//
// Output: true
//
// Explanation:
//
// There is only one element. So the answer is true.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 100
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
    public boolean isArraySpecial(int[] nums) {
        for (int i = 1; i < nums.length; i++) {
            if ((nums[i] % 2) == (nums[i - 1] % 2)) {
                return false;
            }
        }
        return true;            
    }
}
