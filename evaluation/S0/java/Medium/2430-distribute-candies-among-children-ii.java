// Source: https://leetcode.com/problems/distribute-candies-among-children-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integers n and limit.
//
// Return the total number of ways to distribute n candies among 3 children such that no child gets more than limit candies.
//
// Example:
// Input: n = 5, limit = 2
// Output: 3
// Explanation: There are 3 ways to distribute 5 candies such that no child gets more than 2 candies: (1, 2, 2), (2, 1, 2) and (2, 2, 1).
//
// Constraints:
// 1 <= n <= 106
// 	1 <= limit <= 106
//

class Solution {
    public long distributeCandies(int n, int limit) {
        long totalWays = 0;

        for (int i = 0; i <= Math.min(n, limit); i++) {
            for (int j = 0; j <= Math.min(n - i, limit); j++) {
                int k = n - i - j;
                if (k >= 0 && k <= limit) {
                    totalWays++;
                }
            }
        }

        return totalWays;           
    }
}
