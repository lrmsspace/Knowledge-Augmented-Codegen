// Source: https://leetcode.com/problems/valid-permutations-for-di-sequence/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s of length n where s[i] is either:
//
//
// 	'D' means decreasing, or
// 	'I' means increasing.
//
//
// A permutation perm of n + 1 integers of all the integers in the range [0, n] is called a valid permutation if for all valid i:
//
//
// 	If s[i] == 'D', then perm[i] > perm[i + 1], and
// 	If s[i] == 'I', then perm[i] < perm[i + 1].
//
//
// Return the number of valid permutations perm. Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: s = "DID"
// Output: 5
// Explanation: The 5 valid permutations of (0, 1, 2, 3) are:
// (1, 0, 3, 2)
// (2, 0, 3, 1)
// (2, 1, 3, 0)
// (3, 0, 2, 1)
// (3, 1, 2, 0)
//
// Constraints:
// n == s.length
// 	1 <= n <= 200
// 	s[i] is either 'I' or 'D'.
//

int numPermsDISequence(char* s) {
    int n = strlen(s);
    const int MOD = 1000000007;
    int dp[n + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int i = 0; i < n; ++i) {
        int new_dp[n + 1];
        memset(new_dp, 0, sizeof(new_dp));
        if (s[i] == 'I') {
            int cum_sum = 0;
            for (int j = 0; j <= i; ++j) {
                cum_sum = (cum_sum + dp[j]) % MOD;
                new_dp[j + 1] = cum_sum;
            }
        } else { // s[i] == 'D'
            int cum_sum = 0;
            for (int j = i; j >= 0; --j) {
                cum_sum = (cum_sum + dp[j]) % MOD;
                new_dp[j] = cum_sum;
            }
        }
        memcpy(dp, new_dp, sizeof(dp));
    }

    int result = 0;
    for (int i = 0; i <= n; ++i) {
        result = (result + dp[i]) % MOD;
    }
    return result;      
}
