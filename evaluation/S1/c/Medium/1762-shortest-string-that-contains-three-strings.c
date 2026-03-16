// Source: https://leetcode.com/problems/shortest-string-that-contains-three-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given three strings a, b, and c, your task is to find a string that has the minimum length and contains all three strings as substrings.
// If there are multiple such strings, return the lexicographically smallest one.
//
// Return a string denoting the answer to the problem.
//
// Notes
//
//
// 	A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b.
// 	A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: a = "abc", b = "bca", c = "aaa"
// Output: "aaabca"
// Explanation:  We show that "aaabca" contains all the given strings: a = ans[2...4], b = ans[3..5], c = ans[0..2]. It can be shown that the length of the resulting string would be at least 6 and "aaabca" is the lexicographically smallest one.
//
// Constraints:
// 1 <= a.length, b.length, c.length <= 100
// 	a, b, c consist only of lowercase English letters.
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
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

char* minimumString(char* a, char* b, char* c) {
    // Helper function to find the maximum overlap between two strings
    int maxOverlap(const char* s1, const char* s2) {
        int len1 = strlen(s1);
        int len2 = strlen(s2);
        int max_ov = 0;

        for (int i = 1; i <= len1 && i <= len2; i++) {
            if (strncmp(s1 + len1 - i, s2, i) == 0) {
                max_ov = i;
            }
        }
        return max_ov;
    }

    // Helper function to merge two strings with maximum overlap
    char* mergeStrings(const char* s1, const char* s2) {
        int overlap = maxOverlap(s1, s2);
        int len1 = strlen(s1);
        int len2 = strlen(s2);
        char* merged = (char*)malloc(len1 + len2 - overlap + 1);
        strcpy(merged, s1);
        strcpy(merged + len1 - overlap, s2);
        return merged;
    }

    // Generate all permutations of the three strings
    const char* strs[3] = {a, b, c};
    char* candidates[6];
    int idx = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == i) continue;
            for (int k = 0; k < 3; k++) {
                if (k == i || k == j) continue;
                char* firstMerge = mergeStrings(strs[i], strs[j]);
                candidates[idx++] = mergeStrings(firstMerge, strs[k]);
                free(firstMerge);
            }
        }
    }

    // Find the minimum length and lexicographically smallest string
    char* result = candidates[0];
    for (int i = 1; i < 6; i++) {
        if (strlen(candidates[i]) < strlen(result) ||
            (strlen(candidates[i]) == strlen(result) && strcmp(candidates[i], result) < 0)) {
            free(result);
            result = candidates[i];
        } else {
            free(candidates[i]);
        }
    }

    return result;
}
