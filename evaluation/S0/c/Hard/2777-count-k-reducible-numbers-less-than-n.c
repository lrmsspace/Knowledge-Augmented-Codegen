// Source: https://leetcode.com/problems/count-k-reducible-numbers-less-than-n/   |   Difficulty: Hard
//
// Problem Description:
// You are given a binary string s representing a number n in its binary form.
//
// You are also given an integer k.
//
// An integer x is called k-reducible if performing the following operation at most k times reduces it to 1:
//
//
// 	Replace x with the count of set bits in its binary representation.
//
//
// For example, the binary representation of 6 is "110". Applying the operation once reduces it to 2 (since "110" has two set bits). Applying the operation again to 2 (binary "10") reduces it to 1 (since "10" has one set bit).
//
// Return an integer denoting the number of positive integers less than n that are k-reducible.
//
// Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: s = "111", k = 1
//
// Output: 3
//
// Explanation: 
//
// n = 7. The 1-reducible integers less than 7 are 1, 2, and 4.
//
// Constraints:
// 1 <= s.length <= 800
// 	s has no leading zeros.
// 	s consists only of the characters '0' and '1'.
// 	1 <= k <= 5
//

int countKReducibleNumbers(char* s, int k) {
    const int MOD = 1000000007;
    int n = strlen(s);
    int maxBits = n; /* max number of bits we may need to consider */
    int dp[maxBits + 1][maxBits + 1]; /* dp[i][j]: number of ways to form j bits using first i bits */
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        int bit = s[i - 1] - '0';
        for (int j = 0; j <= i; j++) {
            if (bit == 1) {
                dp[i][j] = (dp[i - 1][j] + (j > 0 ? dp[i - 1][j - 1] : 0)) % MOD;
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    /* Precompute the number of steps to reduce a number to 1 */
    int steps[maxBits + 1];
    memset(steps, -1, sizeof(steps));
    steps[0] = -1; /* 0 is not reducible */
    steps[1] = 0;  /* already 1 */
    for (int i = 2; i <= maxBits; i++) {
        int count = 0;
        int x = i;
        while (x != 1) {
            int setBits = 0;
            for (int b = x; b > 0; b &= (b - 1)) setBits++;
            x = setBits;
            count++;
        }
        steps[i] = count;
    }

    /* Count valid numbers */
    int result = 0;
    for (int bits = 1; bits <= maxBits; bits++) {
        if (steps[bits] == k) {
            result = (result + dp[n][bits]) % MOD;
        }
    }

    /* Exclude the number n itself if it is k-reducible */
    int setBitsInN = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') setBitsInN++;
    }
    if (steps[setBitsInN] == k) {
        result = (result - 1 + MOD) % MOD;
    }
    return result;       
}
