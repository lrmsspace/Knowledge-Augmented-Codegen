// Source: https://leetcode.com/problems/merge-strings-alternately/   |   Difficulty: Easy
//
// Problem Description:
// You are given two strings word1 and word2. Merge the strings by adding letters in alternating order, starting with word1. If a string is longer than the other, append the additional letters onto the end of the merged string.
//
// Return the merged string.
//
// Example:
// Input: word1 = "abc", word2 = "pqr"
// Output: "apbqcr"
// Explanation: The merged string will be merged as so:
// word1:  a   b   c
// word2:    p   q   r
// merged: a p b q c r
//
// Constraints:
// 1 <= word1.length, word2.length <= 100
// 	word1 and word2 consist of lowercase English letters.
//

class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        string merged;
        int n1 = word1.size();
        int n2 = word2.size();
        int n = min(n1, n2);
        
        for (int i = 0; i < n; ++i) {
            merged += word1[i];
            merged += word2[i];
        }
        
        if (n1 > n2) {
            merged += word1.substr(n);
        } else if (n2 > n1) {
            merged += word2.substr(n);
        }
        
        return merged;          
    }
};
