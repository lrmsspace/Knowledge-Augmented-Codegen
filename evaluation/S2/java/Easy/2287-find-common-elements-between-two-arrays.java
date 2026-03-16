// Source: https://leetcode.com/problems/find-common-elements-between-two-arrays/   |   Difficulty: Easy
//
// Problem Description:
// You are given two integer arrays nums1 and nums2 of sizes n and m, respectively. Calculate the following values:
//
//
// 	answer1 : the number of indices i such that nums1[i] exists in nums2.
// 	answer2 : the number of indices i such that nums2[i] exists in nums1.
//
//
// Return [answer1,answer2].
//
// Example:
// Input: nums1 = [2,3,2], nums2 = [1,2]
//
// Output: [2,1]
//
// Explanation:
//
// Constraints:
// n == nums1.length
// 	m == nums2.length
// 	1 <= n, m <= 100
// 	1 <= nums1[i], nums2[i] <= 100
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
    public int[] findIntersectionValues(int[] nums1, int[] nums2) {
        int answer1 = 0;
        int answer2 = 0;

        for (int num1 : nums1) {
            for (int num2 : nums2) {
                if (num1 == num2) {
                    answer1++;
                    break; // Move to the next element in nums1
                }
            }
        }

        for (int num2 : nums2) {
            for (int num1 : nums1) {
                if (num2 == num1) {
                    answer2++;
                    break; // Move to the next element in nums2
                }
            }
        }

        return new int[]{answer1, answer2};         
    }
}
