// Source: https://leetcode.com/problems/make-the-xor-of-all-segments-equal-to-zero/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums​​​ and an integer k​​​​​. The XOR of a segment [left, right] where left <= right is the XOR of all the elements with indices between left and right, inclusive: nums[left] XOR nums[left+1] XOR ... XOR nums[right].
//
// Return the minimum number of elements to change in the array such that the XOR of all segments of size k​​​​​​ is equal to zero.
//
// Example:
// Input: nums = [1,2,0,3,0], k = 1
// Output: 3
// Explanation: Modify the array from [1,2,0,3,0] to from [0,0,0,0,0].
//
// Constraints:
// 1 <= k <= nums.length <= 2000
// 	​​​​​​0 <= nums[i] < 210
//

class Solution {
    public int minChanges(int[] nums, int k) {
        int n = nums.length;
        int maxXor = 1 << 10;
        int[][] dp = new int[k][maxXor];
        int[] count = new int[k];
        int[] size = new int[k];

        for (int i = 0; i < n; i++) {
            count[i % k] ^= nums[i];
            size[i % k]++;
        }

        for (int i = 0; i < k; i++) {
            Arrays.fill(dp[i], Integer.MAX_VALUE / 2);
        }

        for (int x = 0; x < maxXor; x++) {
            dp[0][x] = size[0] - (count[0] == x ? 1 : 0);
        }

        for (int i = 1; i < k; i++) {
            int minPrev = Integer.MAX_VALUE;
            for (int x = 0; x < maxXor; x++) {
                minPrev = Math.min(minPrev, dp[i - 1][x]);
            }
            for (int x = 0; x < maxXor; x++) {
                dp[i][x] = Math.min(dp[i - 1][x ^ count[i]] + size[i] - 1,
                                    minPrev + size[i]);
            }
        }

        return dp[k - 1][0];            
    }
}
