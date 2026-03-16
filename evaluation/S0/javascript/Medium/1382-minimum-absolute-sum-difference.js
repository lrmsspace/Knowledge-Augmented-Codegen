// Source: https://leetcode.com/problems/minimum-absolute-sum-difference/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integer arrays nums1 and nums2, both of length n.
//
// The absolute sum difference of arrays nums1 and nums2 is defined as the sum of |nums1[i] - nums2[i]| for each 0 <= i < n (0-indexed).
//
// You can replace at most one element of nums1 with any other element in nums1 to minimize the absolute sum difference.
//
// Return the minimum absolute sum difference after replacing at most one element in the array nums1. Since the answer may be large, return it modulo 109 + 7.
//
// |x| is defined as:
//
//
// 	x if x >= 0, or
// 	-x if x < 0.
//
// Example:
// Input: nums1 = [1,7,5], nums2 = [2,3,5]
// Output: 3
// Explanation: There are two possible optimal solutions:
// - Replace the second element with the first: [1,7,5] => [1,1,5], or
// - Replace the second element with the third: [1,7,5] => [1,5,5].
// Both will yield an absolute sum difference of |1-2| + (|1-3| or |5-3|) + |5-5| = 3.
//
// Constraints:
// n == nums1.length
// 	n == nums2.length
// 	1 <= n <= 105
// 	1 <= nums1[i], nums2[i] <= 105
//

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number}
 */
var minAbsoluteSumDiff = function(nums1, nums2) {
    const MOD = 1e9 + 7;
    const sortedNums1 = [...nums1].sort((a, b) => a - b);
    let totalDiff = 0;
    let maxReduction = 0;

    const binarySearch = (arr, target) => {
        let left = 0;
        let right = arr.length - 1;
        while (left <= right) {
            const mid = Math.floor((left + right) / 2);
            if (arr[mid] === target) {
                return mid;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return left;
    };

    for (let i = 0; i < nums1.length; i++) {
        const diff = Math.abs(nums1[i] - nums2[i]);
        totalDiff = (totalDiff + diff) % MOD;

        const idx = binarySearch(sortedNums1, nums2[i]);
        if (idx < sortedNums1.length) {
            maxReduction = Math.max(maxReduction, diff - Math.abs(sortedNums1[idx] - nums2[i]));
        }
        if (idx > 0) {
            maxReduction = Math.max(maxReduction, diff - Math.abs(sortedNums1[idx - 1] - nums2[i]));
        }
    }

    return (totalDiff - maxReduction + MOD) % MOD;
};