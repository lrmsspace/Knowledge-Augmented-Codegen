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

class Solution {
public:
    int numberOfWays(string s, string t, long long k) {
        const int MOD = 1e9 + 7;
        int n = s.size();
        long long same = 0;
        
        // Count number of rotations of s that equal t
        string ss = s + s;
        for (int i = 0; i < n; i++) {
            if (ss.substr(i, n) == t) {
                same++;
            }
        }
        
        long long diff = n - same;
        
        // Transition matrix
        // | same_next |   = | same   diff | * | same_current |
        // | diff_next |     | diff  n - diff|   | diff_current |
        long long mat[2][2] = {
            {same, diff},
            {diff, n - diff}
        };
        
        // Matrix exponentiation
        long long res[2][2] = {
            {1, 0},
            {0, 1}
        };
        
        while (k > 0) {
            if (k & 1) {
                long long tmp[2][2] = {0};
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        for (int x = 0; x < 2; x++) {
                            tmp[i][j] = (tmp[i][j] + res[i][x] * mat[x][j]) % MOD;
                        }
                    }
                }
                memcpy(res, tmp, sizeof(tmp));
            }
            
            long long tmp[2][2] = {0};
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    for (int x = 0; x < 2; x++) {
                        tmp[i][j] = (tmp[i][j] + mat[i][x] * mat[x][j]) % MOD;
                    }
                }
            }
            memcpy(mat, tmp, sizeof(tmp));
            
            k >>= 1;
        }
        
        return res[0][0] % MOD;         
    }
};
