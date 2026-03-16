// Source: https://leetcode.com/problems/constrained-subsequence-sum/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums and an integer k, return the maximum sum of a non-empty subsequence of that array such that for every two consecutive integers in the subsequence, nums[i] and nums[j], where i < j, the condition j - i <= k is satisfied.
//
// A subsequence of an array is obtained by deleting some number of elements (can be zero) from the array, leaving the remaining elements in their original order.
//
// Example:
// Input: nums = [10,2,-10,5,20], k = 2
// Output: 37
// Explanation: The subsequence is [10, 2, 5, 20].
//
// Constraints:
// 1 <= k <= nums.length <= 105
// 	-104 <= nums[i] <= 104
//

class Solution {
    public int constrainedSubsetSum(int[] nums, int k) {
        int n = nums.length;
        int[] dp = new int[n];
        Deque<Integer> deque = new ArrayDeque<>();
        int maxSum = Integer.MIN_VALUE;

        for (int i = 0; i < n; i++) {
            // If the deque is not empty, add the maximum dp value from the deque
            dp[i] = nums[i] + (deque.isEmpty() ? 0 : Math.max(0, dp[deque.peekFirst()]));
            maxSum = Math.max(maxSum, dp[i]);

            // Maintain the deque to keep only useful indices
            while (!deque.isEmpty() && dp[deque.peekLast()] <= dp[i]) {
                deque.pollLast();
            }
            deque.offerLast(i);

            // Remove indices that are out of the k range
            if (i - deque.peekFirst() >= k) {
                deque.pollFirst();
            }
        }

        return maxSum;                  
    }
}
