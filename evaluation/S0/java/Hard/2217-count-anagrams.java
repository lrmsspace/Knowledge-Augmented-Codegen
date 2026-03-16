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
    public int countAnagrams(String s) {
        String[] words = s.split(" ");
        long mod = 1_000_000_007;
        long result = 1;

        // Precompute factorials and their modular inverses
        int maxLen = 0;
        for (String word : words) {
            maxLen = Math.max(maxLen, word.length());
        }

        long[] fact = new long[maxLen + 1];
        long[] invFact = new long[maxLen + 1];
        fact[0] = 1;
        for (int i = 1; i <= maxLen; i++) {
            fact[i] = (fact[i - 1] * i) % mod;
        }
        invFact[maxLen] = modInverse(fact[maxLen], mod);
        for (int i = maxLen - 1; i >= 0; i--) {
            invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
        }

        for (String word : words) {
            int[] charCount = new int[26];
            for (char c : word.toCharArray()) {
                charCount[c - 'a']++;
            }

            long numerator = fact[word.length()];
            long denominator = 1;
            for (int count : charCount) {
                if (count > 1) {
                    denominator = (denominator * fact[count]) % mod;
                }
            }

            long ways = (numerator * modInverse(denominator, mod)) % mod;
            result = (result * ways) % mod;
        }

        return (int) result;            
    }
}
