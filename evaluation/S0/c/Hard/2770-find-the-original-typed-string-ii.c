// Source: https://leetcode.com/problems/find-the-original-typed-string-ii/   |   Difficulty: Hard
//
// Problem Description:
// Alice is attempting to type a specific string on her computer. However, she tends to be clumsy and may press a key for too long, resulting in a character being typed multiple times.
//
// You are given a string word, which represents the final output displayed on Alice's screen. You are also given a positive integer k.
//
// Return the total number of possible original strings that Alice might have intended to type, if she was trying to type a string of size at least k.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: word = "aabbccdd", k = 7
//
// Output: 5
//
// Explanation:
//
// The possible strings are: "aabbccdd", "aabbccd", "aabbcdd", "aabccdd", and "abbccdd".
//
// Constraints:
// 1 <= word.length <= 5 * 105
//  word consists only of lowercase English letters.
//  1 <= k <= 2000
//

int possibleStringCount(char* word, int k) {
    const int MOD = 1000000007;
    int n = strlen(word);
    int *dp = (int*)calloc(n + 1, sizeof(int));
    if (!dp) return 0;
    dp[0] = 1;
    int windowSum = dp[0];
    for (int i = 1; i <= n; i++) {
        dp[i] = windowSum % MOD;
        if (i >= k) {
            windowSum = (windowSum + dp[i] - dp[i - k] + MOD) % MOD;
        } else {
            windowSum = (windowSum + dp[i]) % MOD;
        }
    }
    int result = dp[n];
    free(dp);
    return result;      
}
