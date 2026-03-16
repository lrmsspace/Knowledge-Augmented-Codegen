// Source: https://leetcode.com/problems/number-of-ways-to-wear-different-hats-to-each-other/   |   Difficulty: Hard
//
// Problem Description:
// There are n people and 40 types of hats labeled from 1 to 40.
//
// Given a 2D integer array hats, where hats[i] is a list of all hats preferred by the ith person.
//
// Return the number of ways that n people can wear different hats from each other.
//
// Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: hats = [[3,4],[4,5],[5]]
// Output: 1
// Explanation: There is only one way to choose hats given the conditions. 
// First person choose hat 3, Second person choose hat 4 and last one hat 5.
//
// Constraints:
// n == hats.length
// 	1 <= n <= 10
// 	1 <= hats[i].length <= 40
// 	1 <= hats[i][j] <= 40
// 	hats[i] contains a list of unique integers.
//

class Solution {
    public int numberWays(List<List<Integer>> hats) {
        int MOD = 1_000_000_007;
        int n = hats.size();
        List<List<Integer>> hatToPeople = new ArrayList<>();
        for (int i = 0; i <= 40; i++) {
            hatToPeople.add(new ArrayList<>());
        }
        for (int person = 0; person < n; person++) {
            for (int hat : hats.get(person)) {
                hatToPeople.get(hat).add(person);
            }
        }

        int totalMasks = 1 << n;
        long[] dp = new long[totalMasks];
        dp[0] = 1;

        for (int hat = 1; hat <= 40; hat++) {
            List<Integer> people = hatToPeople.get(hat);
            long[] newDp = Arrays.copyOf(dp, totalMasks);
            for (int mask = 0; mask < totalMasks; mask++) {
                if (dp[mask] == 0) continue;
                for (int person : people) {
                    if ((mask & (1 << person)) == 0) {
                        int newMask = mask | (1 << person);
                        newDp[newMask] = (newDp[newMask] + dp[mask]) % MOD;
                    }
                }
            }
            dp = newDp;
        }

        return (int) dp[totalMasks - 1];                    
    }
}
