// Source: https://leetcode.com/problems/greatest-english-letter-in-upper-and-lower-case/   |   Difficulty: Easy
//
// Problem Description:
// Given a string of English letters s, return the greatest English letter which occurs as both a lowercase and uppercase letter in s. The returned letter should be in uppercase. If no such letter exists, return an empty string.
//
// An English letter b is greater than another letter a if b appears after a in the English alphabet.
//
// Example:
// Input: s = "lEeTcOdE"
// Output: "E"
// Explanation:
// The letter 'E' is the only letter to appear in both lower and upper case.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists of lowercase and uppercase English letters.
//

char* greatestLetter(char* s) {
    int lower[26] = {0};
    int upper[26] = {0};
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            lower[s[i] - 'a'] = 1;
        } else if (s[i] >= 'A' && s[i] <= 'Z') {
            upper[s[i] - 'A'] = 1;
        }
    }
    for (int i = 25; i >= 0; i--) {
        if (lower[i] && upper[i]) {
            char* result = (char*)malloc(2 * sizeof(char));
            result[0] = 'A' + i;
            result[1] = '\0';
            return result;
        }
    }
    char* empty = (char*)malloc(1 * sizeof(char));
    empty[0] = '\0';
    return empty;       
}
