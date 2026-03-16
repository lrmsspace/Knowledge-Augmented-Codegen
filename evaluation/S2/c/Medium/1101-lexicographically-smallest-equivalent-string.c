// Source: https://leetcode.com/problems/lexicographically-smallest-equivalent-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings of the same length s1 and s2 and a string baseStr.
//
// We say s1[i] and s2[i] are equivalent characters.
//
//
// 	For example, if s1 = "abc" and s2 = "cde", then we have 'a' == 'c', 'b' == 'd', and 'c' == 'e'.
//
//
// Equivalent characters follow the usual rules of any equivalence relation:
//
//
// 	Reflexivity: 'a' == 'a'.
// 	Symmetry: 'a' == 'b' implies 'b' == 'a'.
// 	Transitivity: 'a' == 'b' and 'b' == 'c' implies 'a' == 'c'.
//
//
// For example, given the equivalency information from s1 = "abc" and s2 = "cde", "acd" and "aab" are equivalent strings of baseStr = "eed", and "aab" is the lexicographically smallest equivalent string of baseStr.
//
// Return the lexicographically smallest equivalent string of baseStr by using the equivalency information from s1 and s2.
//
// Example:
// Input: s1 = "parker", s2 = "morris", baseStr = "parser"
// Output: "makkek"
// Explanation: Based on the equivalency information in s1 and s2, we can group their characters as [m,p], [a,o], [k,r,s], [e,i].
// The characters in each group are equivalent and sorted in lexicographical order.
// So the answer is "makkek".
//
// Constraints:
// 1 <= s1.length, s2.length, baseStr <= 1000
// 	s1.length == s2.length
// 	s1, s2, and baseStr consist of lowercase English letters.
//
// Helpful references (internal KB):
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Aho-Corasick Algorithm for Pattern Searching (trie, queue, bitset, aho-corasick, bfs)
//   • When to use: Use when searching for multiple patterns simultaneously within a larger text. It is highly efficient for finding all occurrences of a dictionary of keywords.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a set of patterns, allowing efficient simultaneous searching for all patterns in a text. It typically achieves O(N + M + K) time complexity, where N is text length, M is total pattern length, and K is total matches.
//   • Invariants: All patterns in the dictionary are correctly represented as paths in the trie structure.; For any state `s`, its failure link `fail[s]` points to the longest proper prefix of the string represented by `s` that is also a suffix of `s` and exists in the trie.
//   • Tips: Build the trie first from all patterns, representing each pattern as a path.; Use BFS to construct failure links, pointing to the longest proper prefix of the current state's string that is also a suffix.
//   • Pitfalls: Incorrectly building failure links can lead to wrong matches or infinite loops.; High memory usage if the pattern set is very large or patterns are excessively long.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* smallestEquivalentString(char* s1, char* s2, char* baseStr) {
    // Step 1: Create a mapping for each character to its smallest equivalent character
    char mapping[26];
    for (int i = 0; i < 26; i++) {
        mapping[i] = 'a' + i; // Initialize each character to itself
    }

    // Step 2: Update the mapping based on s1 and s2
    for (int i = 0; s1[i] != '\0'; i++) {
        char c1 = s1[i] - 'a';
        char c2 = s2[i] - 'a';
        char min_char = (mapping[c1] < mapping[c2]) ? mapping[c1] : mapping[c2];
        mapping[c1] = min_char;
        mapping[c2] = min_char;
    }

    // Step 3: Build the result string based on baseStr and the mapping
    int len = strlen(baseStr);
    char* result = (char*)malloc((len + 1) * sizeof(char));
    for (int i = 0; i < len; i++) {
        result[i] = mapping[baseStr[i] - 'a'];
    }
    result[len] = '\0'; // Null-terminate the result string

    return result;      
}
