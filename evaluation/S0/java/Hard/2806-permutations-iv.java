// Source: https://leetcode.com/problems/permutations-iv/   |   Difficulty: Hard
//
// Problem Description:
// Given two integers, n and k, an alternating permutation is a permutation of the first n positive integers such that no two adjacent elements are both odd or both even.
//
// Return the k-th alternating permutation sorted in lexicographical order. If there are fewer than k valid alternating permutations, return an empty list.
//
// Example:
// Input: n = 4, k = 6
//
// Output: [3,4,1,2]
//
// Explanation:
//
// The lexicographically-sorted alternating permutations of [1, 2, 3, 4] are:
//
//
// 	[1, 2, 3, 4]
// 	[1, 4, 3, 2]
// 	[2, 1, 4, 3]
// 	[2, 3, 4, 1]
// 	[3, 2, 1, 4]
// 	[3, 4, 1, 2] ← 6th permutation
// 	[4, 1, 2, 3]
// 	[4, 3, 2, 1]
//
//
// Since k = 6, we return [3, 4, 1, 2].
//
// Constraints:
// 1 <= n <= 100
// 	1 <= k <= 1015
//

class Solution {
    public int[] permute(int n, long k) {
        int oddCount = (n + 1) / 2;
        int evenCount = n / 2;

        long[][][] dp = new long[oddCount + 1][evenCount + 1][2];
        dp[0][0][0] = dp[0][0][1] = 1;

        for (int o = 0; o <= oddCount; o++) {
            for (int e = 0; e <= evenCount; e++) {
                if (o > 0) {
                    dp[o][e][1] += dp[o - 1][e][0] * o;
                }
                if (e > 0) {
                    dp[o][e][0] += dp[o][e - 1][1] * e;
                }
            }
        }

        long totalPermutations = dp[oddCount][evenCount][0] + dp[oddCount][evenCount][1];
        if (k > totalPermutations) {
            return new int[0];
        }

        int[] result = new int[n];
        boolean expectOdd = true;

        for (int i = 0; i < n; i++) {
            for (int num = 1; num <= n; num++) {
                if ((num % 2 == 1 && expectOdd) || (num % 2 == 0 && !expectOdd)) {
                    int oLeft = oddCount - (num % 2 == 1 ? 1 : 0);
                    int eLeft = evenCount - (num % 2 == 0 ? 1 : 0);

                    long count = expectOdd ? dp[oLeft][eLeft][0] : dp[oLeft][eLeft][1];

                    if (k <= count) {
                        result[i] = num;
                        if (num % 2 == 1) {
                            oddCount--;
                        } else {
                            evenCount--;
                        }
                        expectOdd = !expectOdd;
                        break;
                    } else {
                        k -= count;
                    }
                }
            }
        }

        return result;          
    }
}
