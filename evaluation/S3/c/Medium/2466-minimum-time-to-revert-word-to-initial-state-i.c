// Source: https://leetcode.com/problems/minimum-time-to-revert-word-to-initial-state-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string word and an integer k.
//
// At every second, you must perform the following operations:
//
//
// 	Remove the first k characters of word.
// 	Add any k characters to the end of word.
//
//
// Note that you do not necessarily need to add the same characters that you removed. However, you must perform both operations at every second.
//
// Return the minimum time greater than zero required for word to revert to its initial state.
//
// Example:
// Input: word = "abacaba", k = 3
// Output: 2
// Explanation: At the 1st second, we remove characters "aba" from the prefix of word, and add characters "bac" to the end of word. Thus, word becomes equal to "cababac".
// At the 2nd second, we remove characters "cab" from the prefix of word, and add "aba" to the end of word. Thus, word becomes equal to "abacaba" and reverts to its initial state.
// It can be shown that 2 seconds is the minimum time greater than zero required for word to revert to its initial state.
//
// Constraints:
// 1 <= word.length <= 50 
// 	1 <= k <= word.length
// 	word consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Substring Search (string, array, two-pointers, simulation)
//   • When to use: Use KMP to efficiently find all occurrences of a pattern string within a larger text. It is particularly useful when the pattern might appear multiple times or when avoiding redundant text scans is crucial for performance.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently finds all occurrences of a pattern string within a text string by pre-processing the pattern to avoid re-scanning characters in the text. It achieves a time complexity of O(N + M), where N is text length and M is pattern length.
//   • Invariants: The `next` array is correctly pre-computed such that `next[k]` indicates the longest proper prefix of `pattern[0...k-1]` that is also a suffix of `pattern[0...k-1]`.; During the search phase, `text[i-j ... i-1]` always matches `pattern[0 ... j-1]` if `j > 0`.
//   • Tips: Pre-compute the 'next' array (also known as LPS or failure array) for the pattern.; The 'next' array stores the length of the longest proper prefix of the pattern that is also a suffix of the pattern up to that index.
//   • Pitfalls: Incorrectly building the 'next' (LPS) array, especially handling the base cases or transitions.; Off-by-one errors in array indexing for either the text or pattern pointers.
// - Substring Search (string, array, kmp, simulation)
//   • When to use: Use when efficiently finding all occurrences or the first occurrence of a pattern within a larger text, especially when the pattern might have repeating or overlapping prefixes.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that avoids re-scanning characters in the text by pre-processing the pattern to build a 'longest proper prefix suffix' (LPS) array. It achieves optimal O(N + M) time complexity, where N is the text length and M is the pattern length.
//   • Invariants: The `j` pointer always indicates the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `text[0...i-1]`.; The `lps[j]` value stores the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `pattern[0...j-1]`.
//   • Tips: Pre-compute the LPS array (also known as failure function or border array) for the pattern.; The LPS array helps determine the next best match position after a mismatch, avoiding redundant comparisons.
//   • Pitfalls: Incorrectly building the LPS array can lead to wrong matches or infinite loops.; Off-by-one errors when indexing the pattern or text are common.
// - Z-function and its calculation (string, array, two-pointers)
//   • When to use: Use when you need to find the length of the longest common prefix between a string and all its suffixes efficiently. It is fundamental for various string matching and pattern searching problems.
//   • Idea: The Z-function computes an array where each element z[i] is the length of the longest common prefix between the original string and its suffix starting at index i. This algorithm calculates the entire Z-array in O(N) time complexity.
//   • Invariants: For all k < i, z[k] has been correctly computed.; The interval [l, r) always represents the rightmost segment match found so far.
//   • Tips: Leverage previously computed Z-values to avoid redundant comparisons.; Maintain a [l, r) window representing the rightmost segment match found so far.
//   • Pitfalls: Incorrectly handling the base case z[0] (usually set to 0).; Off-by-one errors when calculating the length of the prefix or updating the window.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumTimeToInitialState(char* word, int k) {
    int n = strlen(word);
    char* temp = (char*)malloc((n + 1) * sizeof(char));
    strcpy(temp, word);
    
    for (int time = 1; time <= n; time++) {
        // Remove the first k characters and add any k characters to the end
        char* newWord = (char*)malloc((n + 1) * sizeof(char));
        strncpy(newWord, temp + k, n - k); // Copy the remaining characters after removing the first k
        newWord[n - k] = '\0'; // Null-terminate the string
        
        // Add any k characters to the end (we can just add the removed characters for simplicity)
        strncat(newWord, temp, k); // Add the removed characters to the end
        
        if (strcmp(newWord, word) == 0) {
            free(temp);
            free(newWord);
            return time; // Return the minimum time when it reverts to initial state
        }
        
        free(temp);
        temp = newWord; // Update temp for the next iteration
    }
    
    free(temp);
    return -1; // Should never reach here as it will eventually revert to initial state     
}
