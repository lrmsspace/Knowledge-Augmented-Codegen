// Source: https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s consisting only of characters 'a' and 'b'​​​​.
//
// You can delete any number of characters in s to make s balanced. s is balanced if there is no pair of indices (i,j) such that i < j and s[i] = 'b' and s[j]= 'a'.
//
// Return the minimum number of deletions needed to make s balanced.
//
// Example:
// Input: s = "aababbab"
// Output: 2
// Explanation: You can either:
// Delete the characters at 0-indexed positions 2 and 6 ("aababbab" -> "aaabbb"), or
// Delete the characters at 0-indexed positions 3 and 6 ("aababbab" -> "aabbbb").
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is 'a' or 'b'​​.
//

int minimumDeletions(char* s) {
    int n = strlen(s);
    int* prefixB = (int*)calloc(n + 1, sizeof(int));
    int* suffixA = (int*)calloc(n + 1, sizeof(int));

    for (int i = 1; i <= n; i++) {
        prefixB[i] = prefixB[i - 1] + (s[i - 1] == 'b' ? 1 : 0);
    }

    for (int i = n - 1; i >= 0; i--) {
        suffixA[i] = suffixA[i + 1] + (s[i] == 'a' ? 1 : 0);
    }

    int minDeletions = n; // Initialize with a large number

    for (int i = 0; i <= n; i++) {
        int deletions = prefixB[i] + suffixA[i];
        if (deletions < minDeletions) {
            minDeletions = deletions;
        }
    }

    free(prefixB);
    free(suffixA);

    return minDeletions;        
}
