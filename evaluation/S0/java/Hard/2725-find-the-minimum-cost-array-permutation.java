// Source: https://leetcode.com/problems/find-the-minimum-cost-array-permutation/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums which is a permutation of [0, 1, 2, ..., n - 1]. The score of any permutation of [0, 1, 2, ..., n - 1] named perm is defined as:
//
// score(perm) = |perm[0] - nums[perm[1]]| + |perm[1] - nums[perm[2]]| + ... + |perm[n - 1] - nums[perm[0]]|
//
// Return the permutation perm which has the minimum possible score. If multiple permutations exist with this score, return the one that is lexicographically smallest among them.
//
// Example:
// Input: nums = [1,0,2]
//
// Output: [0,1,2]
//
// Explanation:
//
//
//
// The lexicographically smallest permutation with minimum cost is [0,1,2]. The cost of this permutation is |0 - 0| + |1 - 2| + |2 - 1| = 2.
//
// Constraints:
// 2 <= n == nums.length <= 14
// 	nums is a permutation of [0, 1, 2, ..., n - 1].
//

class Solution {
    public int[] findPermutation(int[] nums) {
        int n = nums.length;
        int size = 1 << n;
        int[][] dp = new int[size][n];
        int[][] parent = new int[size][n];

        for (int mask = 0; mask < size; mask++) {
            for (int last = 0; last < n; last++) {
                dp[mask][last] = Integer.MAX_VALUE;
                parent[mask][last] = -1;
            }
        }

        for (int i = 0; i < n; i++) {
            dp[1 << i][i] = 0;
        }

        for (int mask = 0; mask < size; mask++) {
            for (int last = 0; last < n; last++) {
                if ((mask & (1 << last)) == 0) continue;

                for (int next = 0; next < n; next++) {
                    if ((mask & (1 << next)) != 0) continue;

                    int nextMask = mask | (1 << next);
                    int cost = dp[mask][last] + Math.abs(last - nums[next]);

                    if (cost < dp[nextMask][next]) {
                        dp[nextMask][next] = cost;
                        parent[nextMask][next] = last;
                    }
                }
            }
        }

        int minCost = Integer.MAX_VALUE;
        int lastIndex = -1;

        for (int i = 0; i < n; i++) {
            if (dp[size - 1][i] < minCost) {
                minCost = dp[size - 1][i];
                lastIndex = i;
            }
        }

        int[] result = new int[n];
        int mask = size - 1;

        for (int i = n - 1; i >= 0; i--) {
            result[i] = lastIndex;
            int temp = parent[mask][lastIndex];
            mask ^= (1 << lastIndex);
            lastIndex = temp;
        }

        return result;          
    }
}
