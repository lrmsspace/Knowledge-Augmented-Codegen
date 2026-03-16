// Source: https://leetcode.com/problems/find-the-integer-added-to-array-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given two arrays of equal length, nums1 and nums2.
//
// Each element in nums1 has been increased (or decreased in the case of negative) by an integer, represented by the variable x.
//
// As a result, nums1 becomes equal to nums2. Two arrays are considered equal when they contain the same integers with the same frequencies.
//
// Return the integer x.
//
// Example:
// Input: nums1 = [2,6,4], nums2 = [9,7,5]
//
// Output: 3
//
// Explanation:
//
// The integer added to each element of nums1 is 3.
//
// Constraints:
// 1 <= nums1.length == nums2.length <= 100
// 	0 <= nums1[i], nums2[i] <= 1000
// 	The test cases are generated in a way that there is an integer x such that nums1 can become equal to nums2 by adding x to each element of nums1.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number}
 */
var addedInteger = function(nums1, nums2) {
    if (nums1.length === 0) return 0;
    
    const x = nums2[0] - nums1[0];
    
    for (let i = 1; i < nums1.length; i++) {
        if (nums2[i] - nums1[i] !== x) {
            throw new Error("Invalid input: no such integer x exists");
        }
    }
    
    return x;
};
