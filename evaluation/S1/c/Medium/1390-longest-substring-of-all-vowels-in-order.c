// Source: https://leetcode.com/problems/longest-substring-of-all-vowels-in-order/   |   Difficulty: Medium
//
// Problem Description:
// A string is considered beautiful if it satisfies the following conditions:
//
//
// 	Each of the 5 English vowels ('a', 'e', 'i', 'o', 'u') must appear at least once in it.
// 	The letters must be sorted in alphabetical order (i.e. all 'a's before 'e's, all 'e's before 'i's, etc.).
//
//
// For example, strings "aeiou" and "aaaaaaeiiiioou" are considered beautiful, but "uaeio", "aeoiu", and "aaaeeeooo" are not beautiful.
//
// Given a string word consisting of English vowels, return the length of the longest beautiful substring of word. If no such substring exists, return 0.
//
// A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: word = "aeiaaioaaaaeiiiiouuuooaauuaeiu"
// Output: 13
// Explanation: The longest beautiful substring in word is "aaaaeiiiiouuu" of length 13.
//
// Constraints:
// 1 <= word.length <= 5 * 105
// 	word consists of characters 'a', 'e', 'i', 'o', and 'u'.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int longestBeautifulSubstring(char* word) {
    int max_length = 0;
    int current_length = 0;
    int vowel_count = 0;
    char prev_char = '\0';

    for (int i = 0; word[i] != '\0'; i++) {
        char current_char = word[i];

        if (current_char < prev_char) {
            current_length = 1;
            vowel_count = (current_char == 'a') ? 1 : 0;
        } else if (current_char == prev_char) {
            current_length++;
        } else {
            current_length++;
            vowel_count++;
        }

        if (vowel_count == 5) {
            if (current_length > max_length) {
                max_length = current_length;
            }
        }

        prev_char = current_char;
    }

    return max_length;      
}
