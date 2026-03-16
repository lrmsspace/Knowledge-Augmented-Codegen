// Source: https://leetcode.com/problems/bitwise-xor-of-all-pairings/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed arrays, nums1 and nums2, consisting of non-negative integers. Let there be another array, nums3, which contains the bitwise XOR of all pairings of integers between nums1 and nums2 (every integer in nums1 is paired with every integer in nums2 exactly once).
//
// Return the bitwise XOR of all integers in nums3.
//
// Example:
// Input: nums1 = [2,1,3], nums2 = [10,2,5,0]
// Output: 13
// Explanation:
// A possible nums3 array is [8,0,7,2,11,3,4,1,9,1,6,3].
// The bitwise XOR of all these numbers is 13, so we return 13.
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 105
// 	0 <= nums1[i], nums2[j] <= 109
//

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number}
 */
var xorAllNums = function(nums1, nums2) {
    let xor1 = 0;
    let xor2 = 0;
    for (const num of nums1) {
        xor1 ^= num;
    }
    for (const num of nums2) {
        xor2 ^= num;
    }
    const len1 = nums1.length;
    const len2 = nums2.length;
    let result = 0;
    if (len2 % 2 === 1) {
        result ^= xor1;
    }
    if (len1 % 2 === 1) {
        result ^= xor2;
    }
    return result;
};
