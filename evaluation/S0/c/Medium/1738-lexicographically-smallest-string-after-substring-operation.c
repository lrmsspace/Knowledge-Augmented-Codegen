// Source: https://leetcode.com/problems/lexicographically-smallest-string-after-substring-operation/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s consisting of lowercase English letters. Perform the following operation:
//
//
// 	Select any non-empty substring then replace every letter of the substring with the preceding letter of the English alphabet. For example, 'b' is converted to 'a', and 'a' is converted to 'z'.
//
//
// Return the lexicographically smallest string after performing the operation.
//
// Example:
// Input: s = "cbabc"
//
// Output: "baabc"
//
// Explanation:
//
// Perform the operation on the substring starting at index 0, and ending at index 1 inclusive.
//
// Constraints:
// 1 <= s.length <= 3 * 105
// 	s consists of lowercase English letters
//

char* smallestString(char* s) {
    int n = strlen(s);
    int i = 0;

    // Find the first character that is not 'a'
    while (i < n && s[i] == 'a') {
        i++;
    }

    // If all characters are 'a', change the last character to 'z'
    if (i == n) {
        s[n - 1] = 'z';
        return s;
    }

    // Decrement characters until we hit an 'a' or the end of the string
    while (i < n && s[i] != 'a') {
        s[i]--;
        i++;
    }

    return s;       
}
