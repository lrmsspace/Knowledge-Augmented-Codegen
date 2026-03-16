// Source: https://leetcode.com/problems/form-smallest-number-from-two-digit-arrays/   |   Difficulty: Easy
//
// Problem Description:
// Given two arrays of unique digits nums1 and nums2, return the smallest number that contains at least one digit from each array.
//
// Example:
// Input: nums1 = [4,1,3], nums2 = [5,7]
// Output: 15
// Explanation: The number 15 contains the digit 1 from nums1 and the digit 5 from nums2. It can be proven that 15 is the smallest number we can have.
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 9
// 	1 <= nums1[i], nums2[i] <= 9
// 	All digits in each array are unique.
//

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number}
 */
var minNumber = function(nums1, nums2) {
    const set1 = new Set(nums1);
    let smallestCommon = 10;
    for (const num of nums2) {
        if (set1.has(num)) {
            smallestCommon = Math.min(smallestCommon, num);
        }
    }
    if (smallestCommon !== 10) {
        return smallestCommon;
    }
    return Math.min(Math.min(...nums1), Math.min(...nums2)) * 10 + Math.max(Math.min(...nums1), Math.min(...nums2));
};