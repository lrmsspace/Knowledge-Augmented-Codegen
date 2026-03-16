// Source: https://leetcode.com/problems/maximum-subsequence-score/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed integer arrays nums1 and nums2 of equal length n and a positive integer k. You must choose a subsequence of indices from nums1 of length k.
//
// For chosen indices i0, i1, ..., ik - 1, your score is defined as:
//
//
// 	The sum of the selected elements from nums1 multiplied with the minimum of the selected elements from nums2.
// 	It can defined simply as: (nums1[i0] + nums1[i1] +...+ nums1[ik - 1]) * min(nums2[i0] , nums2[i1], ... ,nums2[ik - 1]).
//
//
// Return the maximum possible score.
//
// A subsequence of indices of an array is a set that can be derived from the set {0, 1, ..., n-1} by deleting some or no elements.
//
// Example:
// Input: nums1 = [1,3,3,2], nums2 = [2,1,3,4], k = 3
// Output: 12
// Explanation: 
// The four possible subsequence scores are:
// - We choose the indices 0, 1, and 2 with score = (1+3+3) * min(2,1,3) = 7.
// - We choose the indices 0, 1, and 3 with score = (1+3+2) * min(2,1,4) = 6. 
// - We choose the indices 0, 2, and 3 with score = (1+3+2) * min(2,3,4) = 12. 
// - We choose the indices 1, 2, and 3 with score = (3+3+2) * min(1,3,4) = 8.
// Therefore, we return the max score, which is 12.
//
// Constraints:
// n == nums1.length == nums2.length
// 	1 <= n <= 105
// 	0 <= nums1[i], nums2[j] <= 105
// 	1 <= k <= n
//

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @param {number} k
 * @return {number}
 */
var maxScore = function(nums1, nums2, k) {
    const n = nums1.length; 
    const pairs = [];

    for (let i = 0; i < n; i++) {
        pairs.push([nums1[i], nums2[i]]);
    }
    pairs.sort((a, b) => b[1] - a[1]);

    const minHeap = [];
    let sum = 0;
    let maxScore = 0;   
    for (let i = 0; i < n; i++) {
        const [num1, num2] = pairs[i];
        sum += num1;
        minHeap.push(num1);
        if (minHeap.length > k) {
            sum -= minHeap.sort((a, b) => a - b).shift();
        }
        if (minHeap.length === k) {
            maxScore = Math.max(maxScore, sum * num2);
        }
    }
    return maxScore;
        
};
