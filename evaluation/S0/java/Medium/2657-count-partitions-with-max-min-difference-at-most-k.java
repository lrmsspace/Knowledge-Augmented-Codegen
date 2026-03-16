// Source: https://leetcode.com/problems/count-partitions-with-max-min-difference-at-most-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k. Your task is to partition nums into one or more non-empty contiguous segments such that in each segment, the difference between its maximum and minimum elements is at most k.
//
// Return the total number of ways to partition nums under this condition.
//
// Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [9,4,1,3,7], k = 4
//
// Output: 6
//
// Explanation:
//
// There are 6 valid partitions where the difference between the maximum and minimum elements in each segment is at most k = 4:
//
//
// 	[[9], [4], [1], [3], [7]]
// 	[[9], [4], [1], [3, 7]]
// 	[[9], [4], [1, 3], [7]]
// 	[[9], [4, 1], [3], [7]]
// 	[[9], [4, 1], [3, 7]]
// 	[[9], [4, 1, 3], [7]]
//
// Constraints:
// 2 <= nums.length <= 5 * 104
// 	1 <= nums[i] <= 109
// 	0 <= k <= 109
//

class Solution {
    public int countPartitions(int[] nums, int k) {
        int n = nums.length;
        long mod = 1_000_000_007;

        long[] dp = new long[n + 1];
        dp[0] = 1;

        Deque<Integer> maxDeque = new ArrayDeque<>();
        Deque<Integer> minDeque = new ArrayDeque<>();

        int left = 0;

        for (int right = 0; right < n; right++) {
            while (!maxDeque.isEmpty() && nums[maxDeque.peekLast()] <= nums[right]) {
                maxDeque.pollLast();
            }
            maxDeque.offerLast(right);

            while (!minDeque.isEmpty() && nums[minDeque.peekLast()] >= nums[right]) {
                minDeque.pollLast();
            }
            minDeque.offerLast(right);

            while (nums[maxDeque.peekFirst()] - nums[minDeque.peekFirst()] > k) {
                if (maxDeque.peekFirst() == left) {
                    maxDeque.pollFirst();
                }
                if (minDeque.peekFirst() == left) {
                    minDeque.pollFirst();
                }
                left++;
            }

            dp[right + 1] = (dp[right + 1] + dp[left]) % mod;
            if (right > left) {
                dp[right + 1] = (dp[right + 1] + dp[right]) % mod;
            }
        }

        return (int) dp[n];         
    }
}
