// Source: https://leetcode.com/problems/unique-binary-search-trees/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the number of structurally unique BST's (binary search trees) which has exactly n nodes of unique values from 1 to n.
//
// Example:
// Input: n = 3
// Output: 5
//
// Constraints:
// 1 <= n <= 19
//

class Solution {
    public int numTrees(int n) {
        int[] dp = new int[n + 1];
        dp[0] = 1;
        dp[1] = 1;

        for (int nodes = 2; nodes <= n; nodes++) {
            for (int root = 1; root <= nodes; root++) {
                int left = root - 1; // number of nodes in left subtree
                int right = nodes - root; // number of nodes in right subtree
                dp[nodes] += dp[left] * dp[right];
            }
        }

        return dp[n];           
    }
}
