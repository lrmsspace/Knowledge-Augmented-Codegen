// Source: https://leetcode.com/problems/delete-characters-to-make-fancy-string/   |   Difficulty: Easy
//
// Problem Description:
// A fancy string is a string where no three consecutive characters are equal.
//
// Given a string s, delete the minimum possible number of characters from s to make it fancy.
//
// Return the final string after the deletion. It can be shown that the answer will always be unique.
//
// Example:
// Input: s = "leeetcode"
// Output: "leetcode"
// Explanation:
// Remove an 'e' from the first group of 'e's to create "leetcode".
// No three consecutive characters are equal, so return "leetcode".
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists only of lowercase English letters.
//

char* makeFancyString(char* s) {
    int len = strlen(s);
    if (len < 3) return s;

    char* result = (char*)malloc((len + 1) * sizeof(char));
    int j = 0; // Pointer for result string

    for (int i = 0; i < len; i++) {
        // Check if the last two characters in result are the same as current character
        if (j >= 2 && result[j - 1] == s[i] && result[j - 2] == s[i]) {
            continue; // Skip this character
        }
        result[j++] = s[i]; // Add current character to result
    }

    result[j] = '\0'; // Null-terminate the result string
    return result;      
}
