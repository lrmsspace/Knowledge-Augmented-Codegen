// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-string-sorted/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s (0-indexed)​​​​​​. You are asked to perform the following operation on s​​​​​​ until you get a sorted string:
//
//
// 	Find the largest index i such that 1 <= i < s.length and s[i] < s[i - 1].
// 	Find the largest index j such that i <= j < s.length and s[k] < s[i - 1] for all the possible values of k in the range [i, j] inclusive.
// 	Swap the two characters at indices i - 1​​​​ and j​​​​​.
// 	Reverse the suffix starting at index i​​​​​​.
//
//
// Return the number of operations needed to make the string sorted. Since the answer can be too large, return it modulo 109 + 7.
//
// Example:
// Input: s = "cba"
// Output: 5
// Explanation: The simulation goes as follows:
// Operation 1: i=2, j=2. Swap s[1] and s[2] to get s="cab", then reverse the suffix starting at 2. Now, s="cab".
// Operation 2: i=1, j=2. Swap s[0] and s[2] to get s="bac", then reverse the suffix starting at 1. Now, s="bca".
// Operation 3: i=2, j=2. Swap s[1] and s[2] to get s="bac", then reverse the suffix starting at 2. Now, s="bac".
// Operation 4: i=1, j=1. Swap s[0] and s[1] to get s="abc", then reverse the suffix starting at 1. Now, s="acb".
// Operation 5: i=2, j=2. Swap s[1] and s[2] to get s="abc", then reverse the suffix starting at 2. Now, s="abc".
//
// Constraints:
// 1 <= s.length <= 3000
// 	s​​​​​​ consists only of lowercase English letters.
//

int makeStringSorted(char* s) {
    const int MOD = 1000000007;
    int n = strlen(s);
    int freq[26];
    memset(freq, 0, sizeof(freq));
    for (int i = 0; i < n; ++i) {
        freq[s[i] - 'a']++;
    }

    long long fact[3001];
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    long long invFact[3001];
    invFact[n] = 1;
    long long base = fact[n];
    // Fermat's little theorem for modular inverse
    long long exp = MOD - 2;
    while (exp) {
        if (exp % 2) invFact[n] = (invFact[n] * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    for (int i = n - 1; i >= 0; --i) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }

    long long res = 0;
    for (int i = 0; i < n; ++i) {
        for (int ch = 0; ch < s[i] - 'a'; ++ch) {
            if (freq[ch] == 0) continue;
            freq[ch]--;
            long long denom = 1;
            for (int k = 0; k < 26; ++k) {
                denom = (denom * invFact[freq[k]]) % MOD;
            }
            res = (res + (fact[n - i - 1] * denom) % MOD) % MOD;
            freq[ch]++;
        }
        freq[s[i] - 'a']--;
    }
    return (int)res;        
}
