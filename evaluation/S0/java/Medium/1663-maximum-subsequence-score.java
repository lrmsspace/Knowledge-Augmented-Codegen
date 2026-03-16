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

class Solution {
    public long maxScore(int[] nums1, int[] nums2, int k) {
        int n = nums1.length;
        int[][] pairs = new int[n][2];
        for (int i = 0; i < n; i++) {
            pairs[i][0] = nums1[i];
            pairs[i][1] = nums2[i];
        }
        Arrays.sort(pairs, (a, b) -> b[1] - a[1]);

        PriorityQueue<Integer> minHeap = new PriorityQueue<>();
        long sum = 0;
        long maxScore = 0;

        for (int i = 0; i < n; i++) {
            minHeap.offer(pairs[i][0]);
            sum += pairs[i][0];

            if (minHeap.size() > k) {
                sum -= minHeap.poll();
            }

            if (minHeap.size() == k) {
                long currentScore = sum * pairs[i][1];
                maxScore = Math.max(maxScore, currentScore);
            }
        }

        return maxScore;            
    }
}
