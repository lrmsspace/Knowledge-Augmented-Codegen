// Source: https://leetcode.com/problems/decode-ways/   |   Difficulty: Medium
//
// Problem Description:
// You have intercepted a secret message encoded as a string of numbers. The message is decoded via the following mapping:
//
// "1" -> 'A'
// "2" -> 'B'
// ...
// "25" -> 'Y'
// "26" -> 'Z'
//
// However, while decoding the message, you realize that there are many different ways you can decode the message because some codes are contained in other codes ("2" and "5" vs "25").
//
// For example, "11106" can be decoded into:
//
//
// 	"AAJF" with the grouping (1, 1, 10, 6)
// 	"KJF" with the grouping (11, 10, 6)
// 	The grouping (1, 11, 06) is invalid because "06" is not a valid code (only "6" is valid).
//
//
// Note: there may be strings that are impossible to decode.
//
// Given a string s containing only digits, return the number of ways to decode it. If the entire string cannot be decoded in any valid way, return 0.
//
// The test cases are generated so that the answer fits in a 32-bit integer.
//
// Example:
// Input: s = "12"
//
// Output: 2
//
// Explanation:
//
// "12" could be decoded as "AB" (1 2) or "L" (12).
//
// Constraints:
// 1 <= s.length <= 100
// 	s contains only digits and may contain leading zero(s).
//

int numDecodings(char* s) {
    int n = strlen(s);
    if (n == 0 || s[0] == '0') {
        return 0;
    }

    int* dp = (int*)calloc(n + 1, sizeof(int));
    dp[0] = 1; // Base case: empty string
    dp[1] = 1; // Base case: first character is valid (not '0')

    for (int i = 2; i <= n; i++) {
        int oneDigit = s[i - 1] - '0';
        int twoDigits = (s[i - 2] - '0') * 10 + oneDigit;

        // Check for valid one-digit decode
        if (oneDigit >= 1 && oneDigit <= 9) {
            dp[i] += dp[i - 1];
        }

        // Check for valid two-digit decode
        if (twoDigits >= 10 && twoDigits <= 26) {
            dp[i] += dp[i - 2];
        }
    }

    int result = dp[n];
    free(dp);
    return result;      
}
