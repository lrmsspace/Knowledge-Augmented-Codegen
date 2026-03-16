// Source: https://leetcode.com/problems/word-pattern/   |   Difficulty: Easy
//
// Problem Description:
// Given a pattern and a string s, find if s follows the same pattern.
//
// Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in s. Specifically:
//
//
// 	Each letter in pattern maps to exactly one unique word in s.
// 	Each unique word in s maps to exactly one letter in pattern.
// 	No two letters map to the same word, and no two words map to the same letter.
//
// Example:
// Input: pattern = "abba", s = "dog cat cat dog"
//
// Output: true
//
// Explanation:
//
// The bijection can be established as:
//
//
// 	'a' maps to "dog".
// 	'b' maps to "cat".
//
// Constraints:
// 1 <= pattern.length <= 300
// 	pattern contains only lower-case English letters.
// 	1 <= s.length <= 3000
// 	s contains only lowercase English letters and spaces ' '.
// 	s does not contain any leading or trailing spaces.
// 	All the words in s are separated by a single space.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - Minimum stack / Minimum queue (queue, stack, simulation)
//   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
//   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
//   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
//   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
//   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool wordPattern(char* pattern, char* s) {
    #define MAX_LEN 3010
    int p2w[26] = {0}; // pattern char to word id
    int w2p[MAX_LEN] = {0}; // word id to pattern char
    int word_id = 1;

    char* token = strtok(s, " ");
    for (int i = 0; pattern[i]; i++) {
        if (!token) return false; // more pattern chars than words

        int p_idx = pattern[i] - 'a';
        int w_idx = 0;
        for (char* ptr = token; *ptr; ptr++) {
            w_idx = w_idx * 31 + (*ptr - 'a' + 1); // simple hash function for word
        }

        if (p2w[p_idx] == 0 && w2p[w_idx] == 0) {
            p2w[p_idx] = word_id;
            w2p[w_idx] = p_idx + 1; // store pattern char index + 1
            word_id++;
        } else if (p2w[p_idx] != w2p[w_idx]) {
            return false; // mismatch in mapping
        }

        token = strtok(NULL, " ");
    }

    return token == NULL; // ensure no extra words left     
}
