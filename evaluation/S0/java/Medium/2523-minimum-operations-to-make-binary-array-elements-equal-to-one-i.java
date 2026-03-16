// Source: https://leetcode.com/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary array nums.
//
// You can do the following operation on the array any number of times (possibly zero):
//
//
// 	Choose any 3 consecutive elements from the array and flip all of them.
//
//
// Flipping an element means changing its value from 0 to 1, and from 1 to 0.
//
// Return the minimum number of operations required to make all elements in nums equal to 1. If it is impossible, return -1.
//
// Example:
// Input: nums = [0,1,1,1,0,0]
//
// Output: 3
//
// Explanation:
// We can do the following operations:
//
//
// 	Choose the elements at indices 0, 1 and 2. The resulting array is nums = [1,0,0,1,0,0].
// 	Choose the elements at indices 1, 2 and 3. The resulting array is nums = [1,1,1,0,0,0].
// 	Choose the elements at indices 3, 4 and 5. The resulting array is nums = [1,1,1,1,1,1].
//
// Constraints:
// 3 <= nums.length <= 105
// 	0 <= nums[i] <= 1
//

class Solution {
    public int minOperations(int[] nums) {
        int n = nums.length;
        int[] dp = new int[n + 1];
        final int INF = (int) 1e9;

        for (int i = 0; i <= n; i++) {
            dp[i] = INF;
        }
        dp[0] = 0;

        for (int i = 0; i < n; i++) {
            if (dp[i] == INF) {
                continue;
            }

            // No flip
            if (nums[i] == 1) {
                dp[i + 1] = Math.min(dp[i + 1], dp[i]);
            }

            // Flip
            if (i + 2 < n) {
                nums[i] ^= 1;
                nums[i + 1] ^= 1;
                nums[i + 2] ^= 1;

                if (nums[i] == 1) {
                    dp[i + 1] = Math.min(dp[i + 1], dp[i] + 1);
                }

                // Revert the flip
                nums[i] ^= 1;
                nums[i + 1] ^= 1;
                nums[i + 2] ^= 1;
            }
        }

        return dp[n] == INF ? -1 : dp[n];           
    }
}
