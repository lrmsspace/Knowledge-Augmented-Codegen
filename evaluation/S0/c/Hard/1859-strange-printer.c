// Source: https://leetcode.com/problems/strange-printer/   |   Difficulty: Hard
//
// Problem Description:
// There is a strange printer with the following two special properties:
//
//
// 	The printer can only print a sequence of the same character each time.
// 	At each turn, the printer can print new characters starting from and ending at any place and will cover the original existing characters.
//
//
// Given a string s, return the minimum number of turns the printer needed to print it.
//
// Example:
// Input: s = "aaabbb"
// Output: 2
// Explanation: Print "aaa" first and then print "bbb".
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists of lowercase English letters.
//

int strangePrinter(char* s) {
    int n = strlen(s);
    int dp[100][100];
    memset(dp, 0, sizeof(dp));
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            dp[i][j] = len; // worst case: print each character separately
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j];
                if (s[k] == s[j]) {
                    cost--; // merge the last print
                }
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }
    return dp[0][n - 1];        
}
