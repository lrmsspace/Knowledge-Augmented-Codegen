// Source: https://leetcode.com/problems/special-binary-string/   |   Difficulty: Hard
//
// Problem Description:
// Special binary strings are binary strings with the following two properties:
//
//
// 	The number of 0's is equal to the number of 1's.
// 	Every prefix of the binary string has at least as many 1's as 0's.
//
//
// You are given a special binary string s.
//
// A move consists of choosing two consecutive, non-empty, special substrings of s, and swapping them. Two strings are consecutive if the last character of the first string is exactly one index before the first character of the second string.
//
// Return the lexicographically largest resulting string possible after applying the mentioned operations on the string.
//
// Example:
// Input: s = "11011000"
// Output: "11100100"
// Explanation: The strings "10" [occuring at s[1]] and "1100" [at s[3]] are swapped.
// This is the lexicographically largest string possible after some number of swaps.
//
// Constraints:
// 1 <= s.length <= 50
// 	s[i] is either '0' or '1'.
// 	s is a special binary string.
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - String Sorts (array, string, recursion)
//   • When to use: Use this algorithm to sort a collection of strings lexicographically, especially when string lengths vary or are large, and the character set is limited.
//   • Idea: This algorithm sorts an array of strings lexicographically by recursively applying a counting sort-like distribution based on characters from most significant to least significant digit. It typically achieves O(N*L + R*L) time complexity, where N is the number of strings, L is the average string length, and R is the radix size.
//   • Invariants: All strings in the current `a[lo...hi]` sub-array share a common prefix of length `d`.; After the distribution pass for character `d`, `aux` contains strings from `a[lo...hi]` stably sorted by their `d`-th character.
//   • Tips: Use an auxiliary array for stable distribution during each pass to maintain relative order.; Implement a cutoff to insertion sort for small sub-arrays to improve performance due to lower overhead.
//   • Pitfalls: Can have high overhead for small N or short strings compared to comparison sorts.; Potentially memory intensive due to the auxiliary array and recursion stack depth proportional to max string length.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: When needing to efficiently represent all substrings of a given string and perform various string operations like counting distinct substrings, finding occurrences, or checking for specific patterns. It provides a compact and powerful data structure for complex string problems.
//   • Idea: A Suffix Automaton is a minimal deterministic finite automaton that recognizes all suffixes of a given string. It compactly represents all substrings of the string, with each state corresponding to an endpos-equivalence class, and can be constructed in linear time O(N).
//   • Invariants: Every state corresponds to a unique endpos-equivalence class of substrings.; For any state, all substrings ending at its endpos set are represented by that state or its ancestors via suffix links.
//   • Tips: Focus on the endpos definition for state equivalence.; Understand the incremental construction process.
//   • Pitfalls: The construction algorithm is non-trivial and prone to off-by-one errors.; Misinterpreting the role of suffix links vs. transition links.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* makeLargestSpecial(char* s) {
    int len = strlen(s);
    if (len <= 2) return s;

    int count = 0, last = 0;
    char** subs = (char**)malloc(len / 2 * sizeof(char*));
    int subsCount = 0;

    for (int i = 0; i < len; ++i) {
        count += (s[i] == '1') ? 1 : -1;
        if (count == 0) {
            /* found a special substring from last to i */
            s[i] = '\0'; /* temporarily terminate substring */
            char* inner = makeLargestSpecial(s + last + 1);
            int innerLen = strlen(inner);
            char* specialSub = (char*)malloc((innerLen + 3) * sizeof(char));
            specialSub[0] = '1';
            strcpy(specialSub + 1, inner);
            specialSub[innerLen + 1] = '0';
            specialSub[innerLen + 2] = '\0';
            subs[subsCount++] = specialSub;
            s[i] = '0'; /* restore */
            last = i + 1;
        }
    }

    /* sort substrings in descending order */
    for (int i = 0; i < subsCount - 1; ++i) {
        for (int j = i + 1; j < subsCount; ++j) {
            if (strcmp(subs[i], subs[j]) < 0) {
                char* temp = subs[i];
                subs[i] = subs[j];
                subs[j] = temp;
            }
        }
    }

    /* concatenate sorted substrings */
    char* result = (char*)malloc((len + 1) * sizeof(char));
    result[0] = '\0';
    for (int i = 0; i < subsCount; ++i) {
        strcat(result, subs[i]);
        free(subs[i]);
    }
    free(subs);

    return result;      
}
