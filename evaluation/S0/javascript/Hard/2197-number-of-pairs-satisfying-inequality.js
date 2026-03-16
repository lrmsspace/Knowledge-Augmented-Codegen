// Source: https://leetcode.com/problems/number-of-pairs-satisfying-inequality/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed integer arrays nums1 and nums2, each of size n, and an integer diff. Find the number of pairs (i, j) such that:
//
//
// 	0 <= i < j <= n - 1 and
// 	nums1[i] - nums1[j] <= nums2[i] - nums2[j] + diff.
//
//
// Return the number of pairs that satisfy the conditions.
//
// Example:
// Input: nums1 = [3,2,5], nums2 = [2,2,1], diff = 1
// Output: 3
// Explanation:
// There are 3 pairs that satisfy the conditions:
// 1. i = 0, j = 1: 3 - 2 <= 2 - 2 + 1. Since i < j and 1 <= 1, this pair satisfies the conditions.
// 2. i = 0, j = 2: 3 - 5 <= 2 - 1 + 1. Since i < j and -2 <= 2, this pair satisfies the conditions.
// 3. i = 1, j = 2: 2 - 5 <= 2 - 1 + 1. Since i < j and -3 <= 2, this pair satisfies the conditions.
// Therefore, we return 3.
//
// Constraints:
// n == nums1.length == nums2.length
// 	2 <= n <= 105
// 	-104 <= nums1[i], nums2[i] <= 104
// 	-104 <= diff <= 104
//

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @param {number} diff
 * @return {number}
 */
var numberOfPairs = function(nums1, nums2, diff) {
    const n = nums1.length;
    const arr = new Array(n);
    for (let i = 0; i < n; i++) {
        arr[i] = nums1[i] - nums2[i];
    }
    let count = 0;
    const sorted = [];
    for (let i = n - 1; i >= 0; i--) {
        const target = arr[i] + diff;
        let left = 0, right = sorted.length;
        while (left < right) {
            const mid = Math.floor((left + right) / 2);
            if (sorted[mid] <= target) {
                right = mid;
            }
            else {                left = mid + 1;
            }
        }
        count += sorted.length - left;
        sorted.splice(left, 0, arr[i]);
    }
    return count;   
};
