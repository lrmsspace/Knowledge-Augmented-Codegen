// Source: https://leetcode.com/problems/find-all-good-strings/   |   Difficulty: Hard
//
// Problem Description:
// Given the strings s1 and s2 of size n and the string evil, return the number of good strings.
//
// A good string has size n, it is alphabetically greater than or equal to s1, it is alphabetically smaller than or equal to s2, and it does not contain the string evil as a substring. Since the answer can be a huge number, return this modulo 109 + 7.
//
// Example:
// Input: n = 2, s1 = "aa", s2 = "da", evil = "b"
// Output: 51 
// Explanation: There are 25 good strings starting with 'a': "aa","ac","ad",...,"az". Then there are 25 good strings starting with 'c': "ca","cc","cd",...,"cz" and finally there is one good string starting with 'd': "da".
//
// Constraints:
// s1.length == n
// 	s2.length == n
// 	s1 <= s2
// 	1 <= n <= 500
// 	1 <= evil.length <= 50
// 	All strings consist of lowercase English letters.
//

int findGoodStrings(int n, char* s1, char* s2, char* evil) {

    const int MOD = 1000000007;
    int evilLen = strlen(evil);

    // Build KMP table for evil string
    int* kmp = (int*)malloc(evilLen * sizeof(int));
    kmp[0] = 0;
    for (int i = 1, j = 0; i < evilLen; ) {
        if (evil[i] == evil[j]) {
            kmp[i++] = ++j;
        } else if (j > 0) {
            j = kmp[j - 1];
        } else {
            kmp[i++] = 0;
        }
    }

    // DP function to count good strings
    int dp[501][51][2][2];
    memset(dp, 0, sizeof(dp));
    dp[0][0][1][1] = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= evilLen; ++j) {
            for (int lower = 0; lower <= 1; ++lower) {
                for (int upper = 0; upper <= 1; ++upper) {
                    if (dp[i][j][lower][upper] == 0) continue;
                    char from = lower ? s1[i] : 'a';
                    char to = upper ? s2[i] : 'z';
                    for (char c = from; c <= to; ++c) {
                        int nj = j;
                        while (nj > 0 && c != evil[nj]) {
                            nj = kmp[nj - 1];
                        }
                        if (c == evil[nj]) {
                            nj++;
                        }
                        if (nj == evilLen) continue; // evil found
                        int nlower = lower && (c == from);
                        int nupper = upper && (c == to);
                        dp[i + 1][nj][nlower][nupper] = (dp[i + 1][nj][nlower][nupper] + dp[i][j][lower][upper]) % MOD;
                    }
                }
            }
        }
    }

    int result = 0;
    for (int j = 0; j < evilLen; ++j) {
        for (int lower = 0; lower <= 1; ++lower) {
            for (int upper = 0; upper <= 1; ++upper) {
                result = (result + dp[n][j][lower][upper]) % MOD;
            }
        }
    }
    free(kmp);
    return result;
            
}
