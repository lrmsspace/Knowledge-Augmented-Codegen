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

int countAnagrams(char* s) {
    const int MOD = 1000000007;
    long long result = 1;
    int fact[100001];
    fact[0] = 1;
    for (int i = 1; i <= 100000; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    char *token = strtok(s, " ");
    while (token) {
        int len = strlen(token);
        int count[26] = {0};
        for (int i = 0; i < len; i++) {
            count[token[i] - 'a']++;
        }
        long long denom = 1;
        for (int i = 0; i < 26; i++) {
            if (count[i] > 1) {
                denom = (denom * fact[count[i]]) % MOD;
            }
        }
        long long ways = (fact[len] * modInverse(denom, MOD)) % MOD;
        result = (result * ways) % MOD;

        token = strtok(NULL, " ");
    }

    return (int)result;     
}
