// Source: https://leetcode.com/problems/reach-end-of-array-with-max-score/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of length n.
//
// Your goal is to start at index 0 and reach index n - 1. You can only jump to indices greater than your current index.
//
// The score for a jump from index i to index j is calculated as (j - i) * nums[i].
//
// Return the maximum possible total score by the time you reach the last index.
//
// Example:
// Input: nums = [1,3,1,5]
//
// Output: 7
//
// Explanation:
//
// First, jump to index 1 and then jump to the last index. The final score is 1 * 1 + 2 * 3 = 7.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

class Solution {
    public long findMaximumScore(List<Integer> nums) {
        int n = nums.size();
        long[] dp = new long[n];
        Deque<Integer> deque = new ArrayDeque<>();
        deque.offerLast(0);

        for (int i = 1; i < n; i++) {
            while (deque.size() >= 2) {
                int j1 = deque.get(deque.size() - 2);
                int j2 = deque.getLast();
                if (dp[j1] + (long)(i - j1) * nums.get(j1) >= dp[j2] + (long)(i - j2) * nums.get(j2)) {
                    deque.pollLast();
                } else {
                    break;
                }
            }

            int j = deque.getLast();
            dp[i] = dp[j] + (long)(i - j) * nums.get(j);

            while (deque.size() >= 2) {
                int j1 = deque.get(deque.size() - 2);
                int j2 = deque.getLast();
                if ((dp[j2] - dp[j1]) * (i - j2) >= (dp[i] - dp[j2]) * (j2 - j1)) {
                    deque.pollLast();
                } else {
                    break;
                }
            }
            deque.offerLast(i);
        }

        return dp[n - 1];           
    }
}
