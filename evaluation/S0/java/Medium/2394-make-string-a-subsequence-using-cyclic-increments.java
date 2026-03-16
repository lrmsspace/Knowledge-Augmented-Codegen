// Source: https://leetcode.com/problems/make-string-a-subsequence-using-cyclic-increments/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed strings str1 and str2.
//
// In an operation, you select a set of indices in str1, and for each index i in the set, increment str1[i] to the next character cyclically. That is 'a' becomes 'b', 'b' becomes 'c', and so on, and 'z' becomes 'a'.
//
// Return true if it is possible to make str2 a subsequence of str1 by performing the operation at most once, and false otherwise.
//
// Note: A subsequence of a string is a new string that is formed from the original string by deleting some (possibly none) of the characters without disturbing the relative positions of the remaining characters.
//
// Example:
// Input: str1 = "abc", str2 = "ad"
// Output: true
// Explanation: Select index 2 in str1.
// Increment str1[2] to become 'd'. 
// Hence, str1 becomes "abd" and str2 is now a subsequence. Therefore, true is returned.
//
// Constraints:
// 1 <= str1.length <= 105
// 	1 <= str2.length <= 105
// 	str1 and str2 consist of only lowercase English letters.
//

class Solution {
    public boolean canMakeSubsequence(String str1, String str2) {
        int n = str1.length();
        int m = str2.length();
        int j = 0; // Pointer for str2

        for (int i = 0; i < n && j < m; i++) {
            char c1 = str1.charAt(i);
            char c2 = str2.charAt(j);

            // Check if we can match c2 by either keeping c1 or incrementing it
            if (c1 == c2 || (c1 == 'z' && c2 == 'a') || (c1 + 1 == c2)) {
                j++; // Move to the next character in str2
            }
        }

        // If we have matched all characters in str2, return true
        return j == m;          
    }
}
