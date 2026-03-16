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



char * mergeAlternately(char * word1, char * word2){
    int len1 = 0, len2 = 0;
    while (word1[len1]) len1++;
    while (word2[len2]) len2++;
    
    int totalLen = len1 + len2;
    char *merged = (char *)malloc((totalLen + 1) * sizeof(char));
    
    int i = 0, j = 0, k = 0;
    while (i < len1 && j < len2) {
        merged[k++] = word1[i++];
        merged[k++] = word2[j++];
    }
    
    while (i < len1) {
        merged[k++] = word1[i++];
    }
    
    while (j < len2) {
        merged[k++] = word2[j++];
    }
    
    merged[k] = '\0';
    return merged;
}
