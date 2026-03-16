// Source: https://leetcode.com/problems/using-a-robot-to-print-the-lexicographically-smallest-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and a robot that currently holds an empty string t. Apply one of the following operations until s and t are both empty:
//
//
// 	Remove the first character of a string s and give it to the robot. The robot will append this character to the string t.
// 	Remove the last character of a string t and give it to the robot. The robot will write this character on paper.
//
//
// Return the lexicographically smallest string that can be written on the paper.
//
// Example:
// Input: s = "zza"
// Output: "azz"
// Explanation: Let p denote the written string.
// Initially p="", s="zza", t="".
// Perform first operation three times p="", s="", t="zza".
// Perform second operation three times p="azz", s="", t="".
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of only English lowercase letters.
//
// Helpful references (internal KB):
// - Minimum stack / Minimum queue (stack, simulation)
//   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
//   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
//   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
//   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
//   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
//   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
//   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
//   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
//   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* robotWithString(char* s) {
    int n = 0;
    while (s[n]) n++;

    int min_from_right[n];
    min_from_right[n - 1] = s[n - 1] - 'a';
    for (int i = n - 2; i >= 0; i--) {
        int curr = s[i] - 'a';
        min_from_right[i] = curr < min_from_right[i + 1] ? curr : min_from_right[i + 1];
    }

    char t_stack[n];
    int t_top = -1;

    char* result = (char*)malloc((n + 1) * sizeof(char));
    int res_len = 0;

    int s_index = 0;
    while (s_index < n || t_top >= 0) {
        if (t_top >= 0 && (s_index == n || t_stack[t_top] - 'a' <= min_from_right[s_index])) {
            result[res_len++] = t_stack[t_top--];
        } else {
            t_stack[++t_top] = s[s_index++];
        }
    }

    result[res_len] = '\0';
    return result;      
}
