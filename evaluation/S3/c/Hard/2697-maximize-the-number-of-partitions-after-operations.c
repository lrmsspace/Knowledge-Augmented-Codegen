// Source: https://leetcode.com/problems/maximize-the-number-of-partitions-after-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and an integer k.
//
// First, you are allowed to change at most one index in s to another lowercase English letter.
//
// After that, do the following partitioning operation until s is empty:
//
//
// 	Choose the longest prefix of s containing at most k distinct characters.
// 	Delete the prefix from s and increase the number of partitions by one. The remaining characters (if any) in s maintain their initial order.
//
//
// Return an integer denoting the maximum number of resulting partitions after the operations by optimally choosing at most one index to change.
//
// Example:
// Input: s = "accca", k = 2
//
// Output: 3
//
// Explanation:
//
// The optimal way is to change s[2] to something other than a and c, for example, b. then it becomes "acbca".
//
// Then we perform the operations:
//
//
// 	The longest prefix containing at most 2 distinct characters is "ac", we remove it and s becomes "bca".
// 	Now The longest prefix containing at most 2 distinct characters is "bc", so we remove it and s becomes "a".
// 	Finally, we remove "a" and s becomes empty, so the procedure ends.
//
//
// Doing the operations, the string is divided into 3 partitions, so the answer is 3.
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists only of lowercase English letters.
// 	1 <= k <= 26
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
// - Substring Search (string, array, two-pointers, simulation)
//   • When to use: Use KMP to efficiently find all occurrences of a pattern string within a larger text. It is particularly useful when the pattern might appear multiple times or when avoiding redundant text scans is crucial for performance.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently finds all occurrences of a pattern string within a text string by pre-processing the pattern to avoid re-scanning characters in the text. It achieves a time complexity of O(N + M), where N is text length and M is pattern length.
//   • Invariants: The `next` array is correctly pre-computed such that `next[k]` indicates the longest proper prefix of `pattern[0...k-1]` that is also a suffix of `pattern[0...k-1]`.; During the search phase, `text[i-j ... i-1]` always matches `pattern[0 ... j-1]` if `j > 0`.
//   • Tips: Pre-compute the 'next' array (also known as LPS or failure array) for the pattern.; The 'next' array stores the length of the longest proper prefix of the pattern that is also a suffix of the pattern up to that index.
//   • Pitfalls: Incorrectly building the 'next' (LPS) array, especially handling the base cases or transitions.; Off-by-one errors in array indexing for either the text or pattern pointers.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxPartitionsAfterOperations(char* s, int k) {
    int n = strlen(s);
    int count[26] = {0};
    int distinct = 0;
    int partitions = 0;

    // Count initial distinct characters
    for (int i = 0; i < n; i++) {
        if (count[s[i] - 'a'] == 0) {
            distinct++;
        }
        count[s[i] - 'a']++;
    }

    // If the number of distinct characters is already less than or equal to k, we can partition it into n parts
    if (distinct <= k) {
        return n;
    }

    // Try changing each character and calculate the resulting partitions
    for (int i = 0; i < n; i++) {
        char original_char = s[i];
        count[original_char - 'a']--;

        // If the original character was unique, decrease distinct count
        if (count[original_char - 'a'] == 0) {
            distinct--;
        }

        // Try changing to a different character
        for (char c = 'a'; c <= 'z'; c++) {
            if (c == original_char) continue;

            count[c - 'a']++;
            if (count[c - 'a'] == 1) {
                distinct++;
            }

            // Calculate partitions with the new character
            int current_partitions = 0;
            int current_distinct = 0;
            for (int j = 0; j < n; j++) {
                if (j == i) continue; // Skip the changed character

                if (count[s[j] - 'a'] > 0) {
                    current_distinct++;
                }

                if (current_distinct > k) {
                    current_partitions++;
                    current_distinct = 1; // Start a new partition with the current character
                }
            }
            current_partitions++; // Account for the last partition

            // Update maximum partitions
            if (current_partitions > partitions) {
                partitions = current_partitions;
            }

            // Revert the change
            count[c - 'a']--;
            if (count[c - 'a'] == 0) {
                distinct--;
            }
        }

        // Revert the original character count
        count[original_char - 'a']++;
        if (count[original_char - 'a'] == 1) {
            distinct++;
        }     
    }
    return partitions;  
}
