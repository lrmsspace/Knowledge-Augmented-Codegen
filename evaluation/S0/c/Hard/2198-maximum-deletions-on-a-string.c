// Source: https://leetcode.com/problems/maximum-deletions-on-a-string/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s consisting of only lowercase English letters. In one operation, you can:
//
//
// 	Delete the entire string s, or
// 	Delete the first i letters of s if the first i letters of s are equal to the following i letters in s, for any i in the range 1 <= i <= s.length / 2.
//
//
// For example, if s = "ababc", then in one operation, you could delete the first two letters of s to get "abc", since the first two letters of s and the following two letters of s are both equal to "ab".
//
// Return the maximum number of operations needed to delete all of s.
//
// Example:
// Input: s = "abcabcdabc"
// Output: 2
// Explanation:
// - Delete the first 3 letters ("abc") since the next 3 letters are equal. Now, s = "abcdabc".
// - Delete all the letters.
// We used 2 operations so return 2. It can be proven that 2 is the maximum number of operations needed.
// Note that in the second operation we cannot delete "abc" again because the next occurrence of "abc" does not happen in the next 3 letters.
//
// Constraints:
// 1 <= s.length <= 4000
// 	s consists only of lowercase English letters.
//

int deleteString(char* s) {
    int n = strlen(s);
    int dp[n + 1];
    memset(dp, 0, sizeof(dp));
    for (int i = n - 1; i >= 0; --i) {
        dp[i] = 1; /* at least delete the whole string */
        for (int l = 1; i + 2 * l <= n; ++l) {
            if (strncmp(&s[i], &s[i + l], l) == 0) {
                if (dp[i + l] + 1 > dp[i]) {
                    dp[i] = dp[i + l] + 1;
                }
            }
        }
    }
    return dp[0];       
}
