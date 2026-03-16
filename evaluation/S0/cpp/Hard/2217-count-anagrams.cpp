// Source: https://leetcode.com/problems/count-anagrams/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s containing one or more words. Every consecutive pair of words is separated by a single space ' '.
//
// A string t is an anagram of string s if the ith word of t is a permutation of the ith word of s.
//
//
// 	For example, "acb dfe" is an anagram of "abc def", but "def cab" and "adc bef" are not.
//
//
// Return the number of distinct anagrams of s. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: s = "too hot"
// Output: 18
// Explanation: Some of the anagrams of the given string are "too hot", "oot hot", "oto toh", "too toh", and "too oht".
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters and spaces ' '.
// 	There is single space between consecutive words.
//

class Solution {
public:
    int countAnagrams(string s) {
        const int MOD = 1e9 + 7;
        long long result = 1;
        long long fact[100001];
        fact[0] = 1;
        
        for (int i = 1; i <= 100000; i++) {
            fact[i] = (fact[i - 1] * i) % MOD;
        }
        
        auto modInverse = [](long long a, long long mod) {
            long long m0 = mod, t, q;
            long long x0 = 0, x1 = 1;
            
            if (mod == 1) return 0LL;
            
            while (a > 1) {
                q = a / mod;
                t = mod;
                mod = a % mod, a = t;
                t = x0;
                x0 = x1 - q * x0;
                x1 = t;
            }
            
            if (x1 < 0) x1 += m0;
            return x1;
        };
        
        int n = s.size();
        int i = 0;
        
        while (i < n) {
            while (i < n && s[i] == ' ') i++;
            if (i >= n) break;
            
            int count[26] = {0};
            int len = 0;
            
            while (i < n && s[i] != ' ') {
                count[s[i] - 'a']++;
                len++;
                i++;
            }
            
            long long denom = 1;
            for (int c : count) {
                denom = (denom * fact[c]) % MOD;
            }
            
            result = (result * fact[len]) % MOD;
            result = (result * modInverse(denom, MOD)) % MOD;
        }
        
        return (int)result;         
    }
};
