// Source: https://leetcode.com/problems/valid-word/   |   Difficulty: Easy
//
// Problem Description:
// A word is considered valid if:
//
//
// 	It contains a minimum of 3 characters.
// 	It contains only digits (0-9), and English letters (uppercase and lowercase).
// 	It includes at least one vowel.
// 	It includes at least one consonant.
//
//
// You are given a string word.
//
// Return true if word is valid, otherwise, return false.
//
// Example:
// Input: word = "234Adas"
//
// Output: true
//
// Explanation:
//
// This word satisfies the conditions.
//
// Constraints:
// 1 <= word.length <= 20
// 	word consists of English uppercase and lowercase letters, digits, '@', '#', and '$'.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool isValid(char* word) {
    int length = 0;
    int has_vowel = 0;
    int has_consonant = 0;
    char c;
    while ((c = word[length]) != '\0') {
        if (!((c >= '0' && c <= '9') ||
              (c >= 'A' && c <= 'Z') ||
              (c >= 'a' && c <= 'z'))) {
            return false;
        }
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            char lower_c = (c >= 'A' && c <= 'Z') ? (c + 32) : c; // convert to lowercase
            if (lower_c == 'a' || lower_c == 'e' || lower_c == 'i' ||
                lower_c == 'o' || lower_c == 'u') {
                has_vowel = 1;
            } else {
                has_consonant = 1;
            }
        }
        length++;
    }
    return (length >= 3) && has_vowel && has_consonant;     
}
