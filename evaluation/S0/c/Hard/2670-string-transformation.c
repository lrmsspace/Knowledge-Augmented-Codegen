// Source: https://leetcode.com/problems/string-transformation/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings s and t of equal length n. You can perform the following operation on the string s:
//
//
// 	Remove a suffix of s of length l where 0 < l < n and append it at the start of s.
// 	For example, let s = 'abcd' then in one operation you can remove the suffix 'cd' and append it in front of s making s = 'cdab'.
//
//
// You are also given an integer k. Return the number of ways in which s can be transformed into t in exactly k operations.
//
// Since the answer can be large, return it modulo 109 + 7.
//
// Example:
// Input: s = "abcd", t = "cdab", k = 2
// Output: 2
// Explanation: 
// First way:
// In first operation, choose suffix from index = 3, so resulting s = "dabc".
// In second operation, choose suffix from index = 3, so resulting s = "cdab".
//
// Second way:
// In first operation, choose suffix from index = 1, so resulting s = "bcda".
// In second operation, choose suffix from index = 1, so resulting s = "cdab".
//
// Constraints:
// 2 <= s.length <= 5 * 105
// 	1 <= k <= 1015
// 	s.length == t.length
// 	s and t consist of only lowercase English alphabets.
//

int numberOfWays(char* s, char* t, long long k) {
    const int MOD = 1000000007;
    int n = strlen(s);
    int matchCount = 0;
    for (int i = 0; i < n; i++) {
        int matched = 1;
        for (int j = 0; j < n; j++) {
            if (s[(i + j) % n] != t[j]) {
                matched = 0;
                break;
            }
        }
        if (matched) matchCount++;
    }

    long long same = matchCount;
    long long diff = n - matchCount;

    long long resSame, resDiff;
    if (k % 2 == 0) {
        resSame = (same * ((k / 2) % MOD)) % MOD;
        resDiff = (diff * ((k / 2) % MOD)) % MOD;
    } else {
        resSame = (diff * ((k / 2 + 1) % MOD)) % MOD;
        resDiff = (same * ((k / 2) % MOD)) % MOD;
    }

    return (int)((resSame + resDiff) % MOD);        
}
