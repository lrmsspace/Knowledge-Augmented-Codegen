// Source: https://leetcode.com/problems/decode-ways-ii/   |   Difficulty: Hard
//
// Problem Description:
// A message containing letters from A-Z can be encoded into numbers using the following mapping:
//
//
// 'A' -> "1"
// 'B' -> "2"
// ...
// 'Z' -> "26"
//
//
// To decode an encoded message, all the digits must be grouped then mapped back into letters using the reverse of the mapping above (there may be multiple ways). For example, "11106" can be mapped into:
//
//
// 	"AAJF" with the grouping (1 1 10 6)
// 	"KJF" with the grouping (11 10 6)
//
//
// Note that the grouping (1 11 06) is invalid because "06" cannot be mapped into 'F' since "6" is different from "06".
//
// In addition to the mapping above, an encoded message may contain the '*' character, which can represent any digit from '1' to '9' ('0' is excluded). For example, the encoded message "1*" may represent any of the encoded messages "11", "12", "13", "14", "15", "16", "17", "18", or "19". Decoding "1*" is equivalent to decoding any of the encoded messages it can represent.
//
// Given a string s consisting of digits and '*' characters, return the number of ways to decode it.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: s = "*"
// Output: 9
// Explanation: The encoded message can represent any of the encoded messages "1", "2", "3", "4", "5", "6", "7", "8", or "9".
// Each of these can be decoded to the strings "A", "B", "C", "D", "E", "F", "G", "H", and "I" respectively.
// Hence, there are a total of 9 ways to decode "*".
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is a digit or '*'.
//

int numDecodings(char* s) {
    const int MOD = 1000000007;
    int n = strlen(s);
    long dp0 = 1; // dp[i-2]
    long dp1 = 0; // dp[i-1]
    // Initialize dp1 based on first character
    if (s[0] == '0') return 0;
    else if (s[0] == '*') dp1 = 9;
    else dp1 = 1;

    for (int i = 1; i < n; ++i) {
        long dp2 = 0; // dp[i]
        char curr = s[i];
        char prev = s[i - 1];

        // Single character decoding
        if (curr == '*') {
            dp2 = (dp2 + 9 * dp1) % MOD;
        } else if (curr != '0') {
            dp2 = (dp2 + dp1) % MOD;
        }

        // Two character decoding
        if (prev == '*') {
            if (curr == '*') {
                dp2 = (dp2 + 15 * dp0) % MOD; // 11-19 and 21-26
            } else if (curr <= '6') {
                dp2 = (dp2 + 2 * dp0) % MOD; // 1x and 2x
            } else {
                dp2 = (dp2 + dp0) % MOD; // only 1x
            }
        } else if (prev == '1') {
            if (curr == '*') {
                dp2 = (dp2 + 9 * dp0) % MOD; // 11-19
            } else {
                dp2 = (dp2 + dp0) % MOD; // 10-19
            }
        } else if (prev == '2') {
            if (curr == '*') {
                dp2 = (dp2 + 6 * dp0) % MOD; // 21-26
            } else if (curr <= '6') {
                dp2 = (dp2 + dp0) % MOD; // 20-26
            }
        }

        dp0 = dp1;
        dp1 = dp2;
    }

    return (int)dp1;        
}
