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

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number}
 */
var minimumAddedInteger = function(nums1, nums2) {
    const countMap1 = new Map();
    for (const num of nums1) {
        countMap1.set(num, (countMap1.get(num) || 0) + 1);
    }
    const countMap2 = new Map();
    for (const num of nums2) {
        countMap2.set(num, (countMap2.get(num) || 0) + 1);
    }
    let x = null;
    for (const [num, count] of countMap2.entries()) {
        const countInNums1 = countMap1.get(num) || 0;
        if (countInNums1 < count) {
            const candidateX = num - (countInNums1 > 0 ? num : 0);
            if (x === null) {
                x = candidateX;
            }
            if (x !== candidateX) {
                return null; // Inconsistent x, should not happen based on problem constraints
            }
        }
    }
    return x;
};
