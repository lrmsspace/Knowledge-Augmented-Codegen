// Source: https://leetcode.com/problems/lexicographically-smallest-beautiful-string/   |   Difficulty: Hard
//
// Problem Description:
// A string is beautiful if:
//
//
// 	It consists of the first k letters of the English lowercase alphabet.
// 	It does not contain any substring of length 2 or more which is a palindrome.
//
//
// You are given a beautiful string s of length n and a positive integer k.
//
// Return the lexicographically smallest string of length n, which is larger than s and is beautiful. If there is no such string, return an empty string.
//
// A string a is lexicographically larger than a string b (of the same length) if in the first position where a and b differ, a has a character strictly larger than the corresponding character in b.
//
//
// 	For example, "abcd" is lexicographically larger than "abcc" because the first position they differ is at the fourth character, and d is greater than c.
//
// Example:
// Input: s = "abcz", k = 26
// Output: "abda"
// Explanation: The string "abda" is beautiful and lexicographically larger than the string "abcz".
// It can be proven that there is no string that is lexicographically larger than the string "abcz", beautiful, and lexicographically smaller than the string "abda".
//
// Constraints:
// 1 <= n == s.length <= 105
// 	4 <= k <= 26
// 	s is a beautiful string.
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

char* smallestBeautifulString(char* s, int k) {
    int n = strlen(s);
    char* result = (char*)malloc((n + 1) * sizeof(char));
    strcpy(result, s);

    for (int i = n - 1; i >= 0; i--) {
        for (char c = result[i] + 1; c < 'a' + k; c++) {
            if ((i > 0 && result[i - 1] == c) || (i > 1 && result[i - 2] == c)) {
                continue;
            }
            result[i] = c;
            for (int j = i + 1; j < n; j++) {
                for (char next_c = 'a'; next_c < 'a' + k; next_c++) {
                    if ((j > 0 && result[j - 1] == next_c) || (j > 1 && result[j - 2] == next_c)) {
                        continue;
                    }
                    result[j] = next_c;
                    break;
                }
            }
            return result;
        }
    }

    free(result);
    return "";      
}
