// Source: https://leetcode.com/problems/number-of-beautiful-partitions/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s that consists of the digits '1' to '9' and two integers k and minLength.
//
// A partition of s is called beautiful if:
//
//
// 	s is partitioned into k non-intersecting substrings.
// 	Each substring has a length of at least minLength.
// 	Each substring starts with a prime digit and ends with a non-prime digit. Prime digits are '2', '3', '5', and '7', and the rest of the digits are non-prime.
//
//
// Return the number of beautiful partitions of s. Since the answer may be very large, return it modulo 109 + 7.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "23542185131", k = 3, minLength = 2
// Output: 3
// Explanation: There exists three ways to create a beautiful partition:
// "2354 | 218 | 5131"
// "2354 | 21851 | 31"
// "2354218 | 51 | 31"
//
// Constraints:
// 1 <= k, minLength <= s.length <= 1000
// 	s consists of the digits '1' to '9'.
//

int beautifulPartitions(char* s, int k, int minLength) {
    const int MOD = 1000000007;
    int n = strlen(s);
    int isPrime[10] = {0,0,1,1,0,1,0,1,0,0}; // index 0-9
    if (!isPrime[s[0]-'0'] || isPrime[s[n-1]-'0']) return 0;

    // dp[i][j]: number of ways to partition first i chars into j parts
    int dp[1001][1001];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    for (int i = minLength; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            // Check if we can make a cut before position i
            if (isPrime[s[i - minLength] - '0'] && !isPrime[s[i - 1] - '0']) {
                for (int p = minLength; p <= i; ++p) {
                    dp[i][j] = (dp[i][j] + dp[i - p][j - 1]) % MOD;
                }
            }
        }
    }

    return dp[n][k];        
}
