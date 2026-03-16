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

int addedInteger(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int x = nums2[0] - nums1[0];
    return x;       
}
