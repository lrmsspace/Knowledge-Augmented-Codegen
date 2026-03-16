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

class Solution {
public:
    int makeStringSorted(string s) {
        const int MOD = 1e9 + 7;
        int n = s.size();
        vector<long long> fact(n + 1, 1), invFact(n + 1, 1);
        
        // Precompute factorials and inverse factorials
        for (int i = 1; i <= n; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }
        invFact[n] = modInverse(fact[n], MOD);
        for (int i = n - 1; i >= 0; i--) {
            invFact[i] = invFact[i + 1] * (i + 1) % MOD;
        }
        
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }
        
        long long result = 0;
        
        for (int i = 0; i < n; i++) {
            for (int c = 0; c < s[i] - 'a'; c++) {
                if (count[c] == 0) continue;
                
                count[c]--;
                long long denom = 1;
                for (int k = 0; k < 26; k++) {
                    denom = denom * invFact[count[k]] % MOD;
                }
                
                long long ways = fact[n - i - 1] * denom % MOD;
                result = (result + ways) % MOD;
                count[c]++;
            }
            count[s[i] - 'a']--;
        }
        
        return (int)result;         
    }
};
