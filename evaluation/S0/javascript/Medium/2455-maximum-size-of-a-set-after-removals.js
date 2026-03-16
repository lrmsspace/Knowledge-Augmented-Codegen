// Source: https://leetcode.com/problems/maximum-size-of-a-set-after-removals/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed integer arrays nums1 and nums2 of even length n.
//
// You must remove n / 2 elements from nums1 and n / 2 elements from nums2. After the removals, you insert the remaining elements of nums1 and nums2 into a set s.
//
// Return the maximum possible size of the set s.
//
// Example:
// Input: nums1 = [1,2,1,2], nums2 = [1,1,1,1]
// Output: 2
// Explanation: We remove two occurences of 1 from nums1 and nums2. After the removals, the arrays become equal to nums1 = [2,2] and nums2 = [1,1]. Therefore, s = {1,2}.
// It can be shown that 2 is the maximum possible size of the set s after the removals.
//
// Constraints:
// n == nums1.length == nums2.length
// 	1 <= n <= 2 * 104
// 	n is even.
// 	1 <= nums1[i], nums2[i] <= 109
//

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number}
 */
var maximumSetSize = function(nums1, nums2) {
    const n = nums1.length;
    const freqMap1 = new Map();
    const freqMap2 = new Map();
    for (let i = 0; i < n; i++) {
        freqMap1.set(nums1[i], (freqMap1.get(nums1[i]) || 0) + 1);
        freqMap2.set(nums2[i], (freqMap2.get(nums2[i]) || 0) + 1);
    }
    let commonElements = 0;
    for (const [num, count1] of freqMap1.entries()) {
        if (freqMap2.has(num)) {
            const count2 = freqMap2.get(num);
            commonElements += Math.min(count1, count2);
        }
    }
    const maxRemovals = n / 2;
    const removalsFromCommon = Math.min(commonElements, maxRemovals);
    const totalUniqueElements = new Set([...nums1, ...nums2]).size;
    return totalUniqueElements - removalsFromCommon;
};
