// Source: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, return the lexicographically smallest subsequence of s that contains all the distinct characters of s exactly once.
//
// Example:
// Input: s = "bcabc"
// Output: "abc"
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists of lowercase English letters.
//
//
//  
// Note: This question is the same as 316: https://leetcode.com/problems/remove-duplicate-letters/
//
// Helpful references (internal KB):
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
//   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
//   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
//   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
//   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
//   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* smallestSubsequence(char* s) {
    int freq[26] = {0}; // Frequency of each character
    int inStack[26] = {0}; // Whether a character is in the stack
    char stack[1001]; // Stack to build the result
    int top = -1; // Top of the stack

    // Count frequency of each character in the input string
    for (char* p = s; *p; p++) {
        freq[*p - 'a']++;
    }

    for (char* p = s; *p; p++) {
        char c = *p;
        int idx = c - 'a';
        freq[idx]--; // Decrease frequency as we process the character

        if (inStack[idx]) {
            continue; // Skip if character is already in stack
        }

        // Pop characters from stack if they are greater than current character
        // and they will appear later (frequency > 0)
        while (top >= 0 && stack[top] > c && freq[stack[top] - 'a'] > 0) {
            inStack[stack[top] - 'a'] = 0; // Mark popped character as not in stack
            top--; // Pop from stack
        }

        stack[++top] = c; // Push current character onto stack
        inStack[idx] = 1; // Mark current character as in stack
    }

    stack[top + 1] = '\0'; // Null-terminate the result string

    return strdup(stack); // Return a copy of the result string     
}
