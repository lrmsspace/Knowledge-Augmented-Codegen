// Source: https://leetcode.com/problems/find-the-integer-added-to-array-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays nums1 and nums2.
//
// From nums1 two elements have been removed, and all other elements have been increased (or decreased in the case of negative) by an integer, represented by the variable x.
//
// As a result, nums1 becomes equal to nums2. Two arrays are considered equal when they contain the same integers with the same frequencies.
//
// Return the minimum possible integer x that achieves this equivalence.
//
// Example:
// Input: nums1 = [4,20,16,12,8], nums2 = [14,18,10]
//
// Output: -2
//
// Explanation:
//
// After removing elements at indices [0,4] and adding -2, nums1 becomes [18,14,10].
//
// Constraints:
// 3 <= nums1.length <= 200
// 	nums2.length == nums1.length - 2
// 	0 <= nums1[i], nums2[i] <= 1000
// 	The test cases are generated in a way that there is an integer x such that nums1 can become equal to nums2 by removing two elements and adding x to each element of nums1.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumAddedInteger(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int count[1001] = {0}; // Frequency array for nums1
    for (int i = 0; i < nums1Size; i++) {
        count[nums1[i]]++;
    }

    int min_x = 1001; // Initialize min_x to a large value
    for (int i = 0; i < nums2Size; i++) {
        if (count[nums2[i]] > 0) {
            count[nums2[i]]--; // Decrease frequency for matched element
        } else {
            // If the element in nums2 is not in nums1, calculate potential x
            for (int j = 0; j < nums1Size; j++) {
                if (count[nums1[j]] > 0) {
                    int potential_x = nums2[i] - nums1[j];
                    if (potential_x < min_x) {
                        min_x = potential_x;
                    }
                }
            }
        }
    }

    return min_x;       
}
