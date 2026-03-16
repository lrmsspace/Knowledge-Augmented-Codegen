// Source: https://leetcode.com/problems/count-the-number-of-special-characters-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string word. A letter c is called special if it appears both in lowercase and uppercase in word, and every lowercase occurrence of c appears before the first uppercase occurrence of c.
//
// Return the number of special letters in word.
//
// Example:
// Input: word = "aaAbcBC"
//
// Output: 3
//
// Explanation:
//
// The special characters are 'a', 'b', and 'c'.
//
// Constraints:
// 1 <= word.length <= 2 * 105
// 	word consists of only lowercase and uppercase English letters.
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numberOfSpecialChars(char* word) {
    int lower[26] = {0};
    int upper[26] = {0};
    int specialCount = 0;

    for (int i = 0; word[i] != '\0'; i++) {
        char c = word[i];
        if (c >= 'a' && c <= 'z') {
            lower[c - 'a'] = 1;
        } else if (c >= 'A' && c <= 'Z') {
            upper[c - 'A'] = 1;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (lower[i] && upper[i]) {
            specialCount++;
        }
    }

    return specialCount;        
}
