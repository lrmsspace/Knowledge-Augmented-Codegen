// Source: https://leetcode.com/problems/minimum-cost-tree-from-leaf-values/   |   Difficulty: Medium
//
// Problem Description:
// Given an array arr of positive integers, consider all binary trees such that:
//
//
// 	Each node has either 0 or 2 children;
// 	The values of arr correspond to the values of each leaf in an in-order traversal of the tree.
// 	The value of each non-leaf node is equal to the product of the largest leaf value in its left and right subtree, respectively.
//
//
// Among all possible binary trees considered, return the smallest possible sum of the values of each non-leaf node. It is guaranteed this sum fits into a 32-bit integer.
//
// A node is a leaf if and only if it has zero children.
//
// Example:
// Input: arr = [6,2,4]
// Output: 32
// Explanation: There are two possible trees shown.
// The first has a non-leaf node sum 36, and the second has non-leaf node sum 32.
//
// Constraints:
// 2 <= arr.length <= 40
// 	1 <= arr[i] <= 15
// 	It is guaranteed that the answer fits into a 32-bit signed integer (i.e., it is less than 231).
//

class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
        vector<vector<int>> maxLeaf(n, vector<int>(n, 0));

        for (int i = 0; i < n; ++i) {
            maxLeaf[i][i] = arr[i];
            dp[i][i] = 0;
        }

        for (int length = 2; length <= n; ++length) {
            for (int i = 0; i <= n - length; ++i) {
                int j = i + length - 1;
                for (int k = i; k < j; ++k) {
                    maxLeaf[i][j] = max(maxLeaf[i][j], max(maxLeaf[i][k], maxLeaf[k + 1][j]));
                    int cost = dp[i][k] + dp[k + 1][j] + maxLeaf[i][k] * maxLeaf[k + 1][j];
                    dp[i][j] = min(dp[i][j], cost);
                }
            }
        }

        return dp[0][n - 1];            
    }
};
