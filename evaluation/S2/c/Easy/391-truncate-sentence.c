// Source: https://leetcode.com/problems/truncate-sentence/   |   Difficulty: Easy
//
// Problem Description:
// A sentence is a list of words that are separated by a single space with no leading or trailing spaces. Each of the words consists of only uppercase and lowercase English letters (no punctuation).
//
//
// 	For example, "Hello World", "HELLO", and "hello world hello world" are all sentences.
//
//
// You are given a sentence s​​​​​​ and an integer k​​​​​​. You want to truncate s​​​​​​ such that it contains only the first k​​​​​​ words. Return s​​​​​​ after truncating it.
//
// Example:
// Input: s = "Hello how are you Contestant", k = 4
// Output: "Hello how are you"
// Explanation:
// The words in s are ["Hello", "how" "are", "you", "Contestant"].
// The first 4 words are ["Hello", "how", "are", "you"].
// Hence, you should return "Hello how are you".
//
// Constraints:
// 1 <= s.length <= 500
// 	k is in the range [1, the number of words in s].
// 	s consist of only lowercase and uppercase English letters and spaces.
// 	The words in s are separated by a single space.
// 	There are no leading or trailing spaces.
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

char* truncateSentence(char* s, int k) {
    char* result = (char*)malloc(strlen(s) + 1); // Allocate memory for the result
    int wordCount = 0;
    int i = 0, j = 0;

    while (s[i] != '\0' && wordCount < k) {
        if (s[i] == ' ') {
            wordCount++;
        }
        result[j++] = s[i++];
    }

    result[j] = '\0'; // Null-terminate the result string
    return result;      
}
