// Source: https://leetcode.com/problems/advantage-shuffle/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays nums1 and nums2 both of the same length. The advantage of nums1 with respect to nums2 is the number of indices i for which nums1[i] > nums2[i].
//
// Return any permutation of nums1 that maximizes its advantage with respect to nums2.
//
// Example:
// Input: nums1 = [2,7,11,15], nums2 = [1,10,4,11]
// Output: [2,11,7,15]
//
// Constraints:
// 1 <= nums1.length <= 105
// 	nums2.length == nums1.length
// 	0 <= nums1[i], nums2[i] <= 109
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
 * @return {number[]}
 */
var advantageCount = function(nums1, nums2) {
    const n = nums1.length;
    const sortedNums1 = [...nums1].sort((a, b) => a - b);
    const indexedNums2 = nums2.map((num, idx) => [num, idx]).sort((a, b) => a[0] - b[0]);
    
    const result = new Array(n);
    let left = 0, right = n - 1;
    
    for (const [num2, idx2] of indexedNums2) {
        if (sortedNums1[left] > num2) {
            result[idx2] = sortedNums1[left];
            left++;
        } else {
            result[idx2] = sortedNums1[right];
            right--;
        }
    }
    
    return result;
};
