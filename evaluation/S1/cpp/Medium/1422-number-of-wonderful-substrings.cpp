// Source: https://leetcode.com/problems/number-of-wonderful-substrings/   |   Difficulty: Medium
//
// Problem Description:
// A wonderful string is a string where at most one letter appears an odd number of times.
//
//
// 	For example, "ccjjc" and "abab" are wonderful, but "ab" is not.
//
//
// Given a string word that consists of the first ten lowercase English letters ('a' through 'j'), return the number of wonderful non-empty substrings in word. If the same substring appears multiple times in word, then count each occurrence separately.
//
// A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: word = "aba"
// Output: 4
// Explanation: The four wonderful substrings are underlined below:
// - "aba" -> "a"
// - "aba" -> "b"
// - "aba" -> "a"
// - "aba" -> "aba"
//
// Constraints:
// 1 <= word.length <= 105
// 	word consists of lowercase English letters from 'a' to 'j'.
//
// Helpful references (internal KB):
// - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-2d)
//   • When to use: Use when efficiently finding all occurrences of a pattern in a text, analyzing string periodicity, or counting distinct substrings. It is especially useful for processing extremely long or recursively defined strings where explicit construction is impossible.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm leverages a precomputed prefix function (LPS array) to avoid redundant comparisons during string searching, achieving linear time complexity. The prefix function itself determines the longest proper prefix of a string that is also a suffix, enabling various string property analyses in O(N) time.
//   • Invariants: For any index `i`, `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix.
//   • Tips: The prefix function `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix.; Concatenate pattern, a unique separator, and text (`P + # + T`) to find all pattern occurrences.
//   • Pitfalls: Off-by-one errors with array indexing or the precise definition of the prefix function.; Incorrectly handling the unique separator character in concatenated strings, leading to false matches.
// - Submask Enumeration
//  (number, bitset, enumeration)
//   • When to use: When you need to iterate through all possible submasks of a given bitmask efficiently, typically for problems involving subsets or combinations represented by bits.
//   • Idea: This algorithm efficiently iterates through all submasks of a given bitmask in descending order using a clever bitwise trick. It processes each submask in O(1) time, leading to an overall complexity of O(2^k) where k is the number of set bits in the original mask.
//   • Invariants: Each `s` generated is a valid submask of the original mask `m`.; The value of `s` strictly decreases in each iteration until it reaches 0 (or the loop terminates).
//   • Tips: Always consider processing the submask 0 separately if it's a valid case for your problem.; The iteration naturally generates submasks in strictly descending numerical order.
//   • Pitfalls: Forgetting that the standard loop structure `for (int s = m; s > 0; s = (s - 1) & m)` omits submask 0.; Incorrectly assuming the iteration order is ascending; it is always descending.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {

public:

    long long wonderfulSubstrings(string word) {

        
        long long result = 0;
        int n = word.size();
        int prefixMask = 0;
        long long count[1024] = {0}; // There are 2^10 = 1024 possible masks for 10 letters
        count[0] = 1; // Empty prefix

        for (int i = 0; i < n; ++i) {
            // Update the prefix mask by toggling the bit corresponding to the current character
            prefixMask ^= (1 << (word[i] - 'a'));

            // Count substrings with even counts for all characters
            result += count[prefixMask];

            // Count substrings with exactly one odd count
            for (int j = 0; j < 10; ++j) {
                int toggledMask = prefixMask ^ (1 << j);
                result += count[toggledMask];
            }

            // Update the count of the current prefix mask
            count[prefixMask]++;
        }

        return result;
    }

};
