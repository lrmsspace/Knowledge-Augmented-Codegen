// Source: https://leetcode.com/problems/count-the-number-of-inversions/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and a 2D array requirements, where requirements[i] = [endi, cnti] represents the end index and the inversion count of each requirement.
//
// A pair of indices (i, j) from an integer array nums is called an inversion if:
//
//
// 	i < j and nums[i] > nums[j]
//
//
// Return the number of permutations perm of [0, 1, 2, ..., n - 1] such that for all requirements[i], perm[0..endi] has exactly cnti inversions.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 3, requirements = [[2,2],[0,0]]
//
// Output: 2
//
// Explanation:
//
// The two permutations are:
//
//
// 	[2, 0, 1]
//
// 	
// 		Prefix [2, 0, 1] has inversions (0, 1) and (0, 2).
// 		Prefix [2] has 0 inversions.
// 	
// 	
// 	[1, 2, 0]
// 	
// 		Prefix [1, 2, 0] has inversions (0, 2) and (1, 2).
// 		Prefix [1] has 0 inversions.
//
// Constraints:
// 2 <= n <= 300
// 	1 <= requirements.length <= n
// 	requirements[i] = [endi, cnti]
// 	0 <= endi <= n - 1
// 	0 <= cnti <= 400
// 	The input is generated such that there is at least one i such that endi == n - 1.
// 	The input is generated such that all endi are unique.
//

class Solution {
    public int numberOfPermutations(int n, int[][] requirements) {
        int MOD = 1_000_000_007;

        // Sort requirements by end index
        Arrays.sort(requirements, (a, b) -> Integer.compare(a[0], b[0]));

        // DP array to store the number of ways to form permutations with a certain number of inversions
        int maxInversions = n * (n - 1) / 2;
        long[] dp = new long[maxInversions + 1];
        dp[0] = 1;

        int prevEnd = -1;

        for (int[] req : requirements) {
            int end = req[0];
            int cnt = req[1];
            int len = end - prevEnd; // Length of the current segment

            // New DP array for the current segment
            long[] newDp = new long[maxInversions + 1];

            // Calculate the number of ways to arrange the current segment
            for (int inv = 0; inv <= maxInversions; inv++) {
                if (dp[inv] == 0) continue;

                for (int k = 0; k <= len * (len - 1) / 2; k++) {
                    if (inv + k > maxInversions) break;
                    newDp[inv + k] = (newDp[inv + k] + dp[inv] * countWays(len, k, MOD)) % MOD;
                }
            }

            dp = newDp;
            prevEnd = end;
        }

        return (int) dp[requirements[requirements.length - 1][1]];          
    }
}
