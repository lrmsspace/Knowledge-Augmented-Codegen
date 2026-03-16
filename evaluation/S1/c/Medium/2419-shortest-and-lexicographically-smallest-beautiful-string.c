// Source: https://leetcode.com/problems/shortest-and-lexicographically-smallest-beautiful-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary string s and a positive integer k.
//
// A substring of s is beautiful if the number of 1's in it is exactly k.
//
// Let len be the length of the shortest beautiful substring.
//
// Return the lexicographically smallest beautiful substring of string s with length equal to len. If s doesn't contain a beautiful substring, return an empty string.
//
// A string a is lexicographically larger than a string b (of the same length) if in the first position where a and b differ, a has a character strictly larger than the corresponding character in b.
//
//
// 	For example, "abcd" is lexicographically larger than "abcc" because the first position they differ is at the fourth character, and d is greater than c.
//
// Example:
// Input: s = "100011001", k = 3
// Output: "11001"
// Explanation: There are 7 beautiful substrings in this example:
// 1. The substring "100011001".
// 2. The substring "100011001".
// 3. The substring "100011001".
// 4. The substring "100011001".
// 5. The substring "100011001".
// 6. The substring "100011001".
// 7. The substring "100011001".
// The length of the shortest beautiful substring is 5.
// The lexicographically smallest beautiful substring with length 5 is the substring "11001".
//
// Constraints:
// 1 <= s.length <= 100
// 	1 <= k <= s.length
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

char* shortestBeautifulSubstring(char* s, int k) {
    int n = 0;
    while (s[n] != '\0') n++;

    int min_len = n + 1;
    for (int i = 0; i < n; i++) {
        int count_ones = 0;
        for (int j = i; j < n; j++) {
            if (s[j] == '1') count_ones++;
            if (count_ones == k) {
                int curr_len = j - i + 1;
                if (curr_len < min_len) {
                    min_len = curr_len;
                }
                break;
            }
        }
    }

    if (min_len == n + 1) {
        char* result = (char*)malloc(1);
        result[0] = '\0';
        return result;
    }

    char* best_substring = NULL;
    for (int i = 0; i <= n - min_len; i++) {
        int count_ones = 0;
        for (int j = i; j < i + min_len; j++) {
            if (s[j] == '1') count_ones++;
        }
        if (count_ones == k) {
            char* current_substring = (char*)malloc(min_len + 1);
            for (int j = 0; j < min_len; j++) {
                current_substring[j] = s[i + j];
            }
            current_substring[min_len] = '\0';

            if (best_substring == NULL || strcmp(current_substring, best_substring) < 0) {
                if (best_substring != NULL) {
                    free(best_substring);
                }
                best_substring = current_substring;
            } else {
                free(current_substring);
            }
        }
    }

    return best_substring;      
}
