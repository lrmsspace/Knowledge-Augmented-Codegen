// Source: https://leetcode.com/problems/longest-subsequence-repeated-k-times/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s of length n, and an integer k. You are tasked to find the longest subsequence repeated k times in string s.
//
// A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
//
// A subsequence seq is repeated k times in the string s if seq * k is a subsequence of s, where seq * k represents a string constructed by concatenating seq k times.
//
//
// 	For example, "bba" is repeated 2 times in the string "bababcba", because the string "bbabba", constructed by concatenating "bba" 2 times, is a subsequence of the string "bababcba".
//
//
// Return the longest subsequence repeated k times in string s. If multiple such subsequences are found, return the lexicographically largest one. If there is no such subsequence, return an empty string.
//
// Example:
// Input: s = "letsleetcode", k = 2
// Output: "let"
// Explanation: There are two longest subsequences repeated 2 times: "let" and "ete".
// "let" is the lexicographically largest one.
//
// Constraints:
// n == s.length
// 	2 <= k <= 2000
// 	2 <= n < min(2001, k * 8)
// 	s consists of lowercase English letters.
//

class Solution {
public:
    string longestSubsequenceRepeatedK(string s, int k) {
        string result = "";
        int n = s.size();
        int total = 1 << n;
        
        for (int mask = 1; mask < total; mask++) {
            string subseq = "";
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    subseq += s[i];
                }
            }
            
            // Check if subseq repeated k times is a subsequence of s
            string repeated = "";
            for (int i = 0; i < k; i++) {
                repeated += subseq;
            }
            
            int idxS = 0, idxR = 0;
            while (idxS < n && idxR < repeated.size()) {
                if (s[idxS] == repeated[idxR]) {
                    idxR++;
                }
                idxS++;
            }
            
            if (idxR == repeated.size()) {
                // Valid subsequence
                if (subseq.size() > result.size() || 
                    (subseq.size() == result.size() && subseq > result)) {
                    result = subseq;
                }
            }
        }
        
        return result;          
    }
};
