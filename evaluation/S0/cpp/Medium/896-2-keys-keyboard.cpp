// Source: https://leetcode.com/problems/2-keys-keyboard/   |   Difficulty: Medium
//
// Problem Description:
// There is only one character 'A' on the screen of a notepad. You can perform one of two operations on this notepad for each step:
//
//
// 	Copy All: You can copy all the characters present on the screen (a partial copy is not allowed).
// 	Paste: You can paste the characters which are copied last time.
//
//
// Given an integer n, return the minimum number of operations to get the character 'A' exactly n times on the screen.
//
// Example:
// Input: n = 3
// Output: 3
// Explanation: Initially, we have one character 'A'.
// In step 1, we use Copy All operation.
// In step 2, we use Paste operation to get 'AA'.
// In step 3, we use Paste operation to get 'AAA'.
//
// Constraints:
// 1 <= n <= 1000
//

class Solution {
public:
    int minSteps(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[1] = 0;

        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j * j <= i; ++j) {
                if (i % j == 0) {
                    dp[i] = min(dp[i], dp[j] + (i / j));
                    if (j != 1) {
                        dp[i] = min(dp[i], dp[i / j] + j);
                    }
                }
            }
        }

        return dp[n];           
    }
};
