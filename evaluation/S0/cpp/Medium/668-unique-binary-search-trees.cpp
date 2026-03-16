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
public:
    int numTrees(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = 1; // Base case: there's one unique BST for 0 nodes (empty tree)

        for (int nodes = 1; nodes <= n; ++nodes) {
            for (int root = 1; root <= nodes; ++root) {
                int left = root - 1;          // Number of nodes in the left subtree
                int right = nodes - root;    // Number of nodes in the right subtree
                dp[nodes] += dp[left] * dp[right];
            }
        }

        return dp[n];           
    }
};
