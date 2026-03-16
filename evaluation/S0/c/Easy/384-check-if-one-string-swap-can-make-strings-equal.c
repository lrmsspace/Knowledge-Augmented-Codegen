// Source: https://leetcode.com/problems/check-if-one-string-swap-can-make-strings-equal/   |   Difficulty: Easy
//
// Problem Description:
// You are given two strings s1 and s2 of equal length. A string swap is an operation where you choose two indices in a string (not necessarily different) and swap the characters at these indices.
//
// Return true if it is possible to make both strings equal by performing at most one string swap on exactly one of the strings. Otherwise, return false.
//
// Example:
// Input: s1 = "bank", s2 = "kanb"
// Output: true
// Explanation: For example, swap the first character with the last character of s2 to make "bank".
//
// Constraints:
// 1 <= s1.length, s2.length <= 100
// 	s1.length == s2.length
// 	s1 and s2 consist of only lowercase English letters.
//

bool areAlmostEqual(char* s1, char* s2) {
    int diff_indices[2];
    int diff_count = 0;

    for (int i = 0; s1[i] != '\0'; i++) {
        if (s1[i] != s2[i]) {
            if (diff_count >= 2) {
                return false; // More than 2 differences found
            }
            diff_indices[diff_count] = i;
            diff_count++;
        }
    }

    if (diff_count == 0) {
        return true; // Strings are already equal
    } else if (diff_count == 2) {
        // Check if swapping the differing characters makes the strings equal
        return (s1[diff_indices[0]] == s2[diff_indices[1]] &&
                s1[diff_indices[1]] == s2[diff_indices[0]]);
    } else {
        return false; // Only one difference found, cannot make equal with one swap
    }       
}
