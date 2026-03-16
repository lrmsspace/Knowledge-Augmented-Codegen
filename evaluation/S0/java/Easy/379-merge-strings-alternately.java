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
    public String mergeAlternately(String word1, String word2) {
        StringBuilder merged = new StringBuilder();
        int length1 = word1.length();
        int length2 = word2.length();
        int minLength = Math.min(length1, length2);

        for (int i = 0; i < minLength; i++) {
            merged.append(word1.charAt(i));
            merged.append(word2.charAt(i));
        }

        if (length1 > length2) {
            merged.append(word1.substring(minLength));
        } else if (length2 > length1) {
            merged.append(word2.substring(minLength));
        }

        return merged.toString();           
    }
}
