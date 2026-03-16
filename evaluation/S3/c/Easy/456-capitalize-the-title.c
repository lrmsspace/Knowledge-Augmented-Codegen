// Source: https://leetcode.com/problems/capitalize-the-title/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string title consisting of one or more words separated by a single space, where each word consists of English letters. Capitalize the string by changing the capitalization of each word such that:
//
//
// 	If the length of the word is 1 or 2 letters, change all letters to lowercase.
// 	Otherwise, change the first letter to uppercase and the remaining letters to lowercase.
//
//
// Return the capitalized title.
//
// Example:
// Input: title = "capiTalIze tHe titLe"
// Output: "Capitalize The Title"
// Explanation:
// Since all the words have a length of at least 3, the first letter of each word is uppercase, and the remaining letters are lowercase.
//
// Constraints:
// 1 <= title.length <= 100
// 	title consists of words separated by a single space without any leading or trailing spaces.
// 	Each word consists of uppercase and lowercase English letters and is non-empty.
//
// Helpful references (internal KB):
// - Aho-Corasick Algorithm for Pattern Searching (string, array, aho-corasick, enumeration)
//   • When to use: Use when you need to find all occurrences of a fixed set of patterns (a dictionary) within a larger text efficiently. It is particularly effective for scenarios with many patterns or long texts where patterns might overlap.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a dictionary of patterns, then uses this automaton to search for all pattern occurrences in a text in a single pass. It achieves a time complexity of O(N + M + K) where N is text length, M is total pattern length, and K is total matches.
//   • Invariants: The trie structure correctly represents all prefixes of all patterns in the dictionary.; Each node's failure link points to the longest proper suffix of the string ending at that node which is also a prefix in the trie.
//   • Tips: Build the trie first from all patterns, marking terminal nodes.; Compute failure links using a BFS-like approach, similar to KMP's LPS array.
//   • Pitfalls: Incorrectly building failure links can lead to missed matches or infinite loops.; Forgetting to handle output links (dictionary links) will miss patterns found via failure transitions.
// - Manacher's Algorithm - Finding all sub-p (string, array, enumeration)
//   • When to use: Use when you need to find all palindromic substrings within a given string, or determine the longest palindromic substring, in optimal linear time.
//   • Idea: Manacher's Algorithm efficiently finds the length of the longest palindromic substring centered at each position in a given string, handling both odd and even lengths uniformly via preprocessing. It achieves this in optimal O(N) time complexity.
//   • Invariants: p[i] correctly stores the radius of the longest palindrome centered at i in the transformed string.; The right_boundary always marks the rightmost extent of the largest palindrome found so far.
//   • Tips: Preprocess the string with a unique delimiter to unify odd and even length palindromes.; Leverage the mirror property around the current center to initialize palindrome radii.
//   • Pitfalls: Off-by-one errors when converting `p` array values back to original string indices or lengths.; Incorrectly handling the boundaries of the preprocessed string.
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* capitalizeTitle(char* title) {
    char* result = title; // We can modify the input string directly
    char* word_start = title; // Pointer to the start of the current word

    while (*title) {
        if (*title == ' ') { // End of a word
            int word_length = title - word_start; // Calculate the length of the current word
            if (word_length <= 2) {
                // Convert to lowercase
                for (char* p = word_start; p < title; p++) {
                    if (*p >= 'A' && *p <= 'Z') {
                        *p += ('a' - 'A'); // Convert to lowercase
                    }
                }
            } else {
                // Convert first letter to uppercase and the rest to lowercase
                if (*word_start >= 'a' && *word_start <= 'z') {
                    *word_start -= ('a' - 'A'); // Convert first letter to uppercase
                }
                for (char* p = word_start + 1; p < title; p++) {
                    if (*p >= 'A' && *p <= 'Z') {
                        *p += ('a' - 'A'); // Convert to lowercase
                    }
                }
            }
            word_start = title + 1; // Move to the start of the next word
        }
        title++;
    }

    // Handle the last word after the loop
    int word_length = title - word_start; // Calculate the length of the last word
    if (word_length <= 2) {
        for (char* p = word_start; p < title; p++) {
            if (*p >= 'A' && *p <= 'Z') {
                *p += ('a' - 'A'); // Convert to lowercase
            }
        }
    } else {
        if (*word_start >= 'a' && *word_start <= 'z') {
            *word_start -= ('a' - 'A'); // Convert first letter to uppercase
        }
        for (char* p = word_start + 1; p < title; p++) {
            if (*p >= 'A' && *p <= 'Z') {
                *p += ('a' - 'A'); // Convert to lowercase
            }
        }
    }

    return result;      
}
