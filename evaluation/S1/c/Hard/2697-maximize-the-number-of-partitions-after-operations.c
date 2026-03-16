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
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-2d)
//   • When to use: Use when efficiently finding all occurrences of a pattern in a text, analyzing string periodicity, or counting distinct substrings. It is especially useful for processing extremely long or recursively defined strings where explicit construction is impossible.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm leverages a precomputed prefix function (LPS array) to avoid redundant comparisons during string searching, achieving linear time complexity. The prefix function itself determines the longest proper prefix of a string that is also a suffix, enabling various string property analyses in O(N) time.
//   • Invariants: For any index `i`, `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix.
//   • Tips: The prefix function `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix.; Concatenate pattern, a unique separator, and text (`P + # + T`) to find all pattern occurrences.
//   • Pitfalls: Off-by-one errors with array indexing or the precise definition of the prefix function.; Incorrectly handling the unique separator character in concatenated strings, leading to false matches.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxPartitionsAfterOperations(char* s, int k) {
    int n = strlen(s);
    int freq[26] = {0};
    int distinct = 0;
    int partitions = 0;
    int left = 0, right = 0;

    /* Function to count partitions in the current string */
    auto countPartitions = [&](char *str) {
        int partCount = 0;
        int freqLocal[26] = {0};
        int distinctLocal = 0;
        int l = 0, r = 0;

        while (r < n) {
            if (freqLocal[str[r] - 'a'] == 0) distinctLocal++;
            freqLocal[str[r] - 'a']++;
            while (distinctLocal > k) {
                freqLocal[str[l] - 'a']--;
                if (freqLocal[str[l] - 'a'] == 0) distinctLocal--;
                l++;
            }
            if (r == n - 1 || distinctLocal == k && (r + 1 < n && freqLocal[str[r + 1] - 'a'] == 0)) {
                partCount++;
                memset(freqLocal, 0, sizeof(freqLocal));
                distinctLocal = 0;
                l = r + 1;
            }
            r++;
        }
        return partCount;
    };

    /* Initial partition count without any changes */
    partitions = countPartitions(s);

    /* Try changing each character to every other character */
    for (int i = 0; i < n; i++) {
        char originalChar = s[i];
        for (char c = 'a'; c <= 'z'; c++) {
            if (c == originalChar) continue;
            s[i] = c;
            int newPartitions = countPartitions(s);
            if (newPartitions > partitions) {
                partitions = newPartitions;
            }
        }
        s[i] = originalChar; /* revert change */
    }

    return partitions;      
}
