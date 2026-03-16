// Source: https://leetcode.com/problems/partition-string-into-minimum-beautiful-substrings/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s, partition the string into one or more substrings such that each substring is beautiful.
//
// A string is beautiful if:
//
//
// 	It doesn't contain leading zeros.
// 	It's the binary representation of a number that is a power of 5.
//
//
// Return the minimum number of substrings in such partition. If it is impossible to partition the string s into beautiful substrings, return -1.
//
// A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: s = "1011"
// Output: 2
// Explanation: We can paritition the given string into ["101", "1"].
// - The string "101" does not contain leading zeros and is the binary representation of integer 51 = 5.
// - The string "1" does not contain leading zeros and is the binary representation of integer 50 = 1.
// It can be shown that 2 is the minimum number of beautiful substrings that s can be partitioned into.
//
// Constraints:
// 1 <= s.length <= 15
// 	s[i] is either '0' or '1'.
//

int minimumBeautifulSubstrings(char* s) {
    int n = strlen(s);
    int dp[n + 1];
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        if (s[i - 1] == '0') {
            continue;
        }
        long num = 0;
        for (int j = i; j <= n; ++j) {
            num = (num << 1) + (s[j - 1] - '0');
            long temp = 1;
            while (temp < num) {
                temp *= 5;
            }
            if (temp == num) {
                dp[j] = fmin(dp[j], dp[i - 1] + 1);
            }
        }
    }

    return dp[n] > n ? -1 : dp[n];      
}
