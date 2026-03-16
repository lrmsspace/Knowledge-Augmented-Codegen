// Source: https://leetcode.com/problems/number-of-strings-which-can-be-rearranged-to-contain-substring/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n.
//
// A string s is called good if it contains only lowercase English characters and it is possible to rearrange the characters of s such that the new string contains "leet" as a substring.
//
// For example:
//
//
// 	The string "lteer" is good because we can rearrange it to form "leetr" .
// 	"letl" is not good because we cannot rearrange it to contain "leet" as a substring.
//
//
// Return the total number of good strings of length n.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: n = 4
// Output: 12
// Explanation: The 12 strings which can be rearranged to have "leet" as a substring are: "eelt", "eetl", "elet", "elte", "etel", "etle", "leet", "lete", "ltee", "teel", "tele", and "tlee".
//
// Constraints:
// 1 <= n <= 105
//

int stringCount(int n) {
    const int MOD = 1000000007;
    if (n < 4) return 0;

    // Precompute factorials and modular inverses
    long long fact[n + 1];
    long long invFact[n + 1];
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    invFact[n] = powMod(fact[n], MOD - 2, MOD);
    for (int i = n - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }

    long long totalWays = 0;
    for (int extraChars = 0; extraChars <= n - 4; extraChars++) {
        int totalLength = 4 + extraChars;
        long long waysToChoosePositions = fact[totalLength] * invFact[4] % MOD * invFact[extraChars] % MOD;
        long long waysToChooseExtraChars = powMod(22, extraChars, MOD);
        totalWays = (totalWays + waysToChoosePositions * waysToChooseExtraChars) % MOD;
    }

    return (int)totalWays;      
}
