// Source: https://leetcode.com/problems/find-the-k-th-character-in-string-game-i/   |   Difficulty: Easy
//
// Problem Description:
// Alice and Bob are playing a game. Initially, Alice has a string word = "a".
//
// You are given a positive integer k.
//
// Now Bob will ask Alice to perform the following operation forever:
//
//
// 	Generate a new string by changing each character in word to its next character in the English alphabet, and append it to the original word.
//
//
// For example, performing the operation on "c" generates "cd" and performing the operation on "zb" generates "zbac".
//
// Return the value of the kth character in word, after enough operations have been done for word to have at least k characters.
//
// Example:
// Input: k = 5
//
// Output: "b"
//
// Explanation:
//
// Initially, word = "a". We need to do the operation three times:
//
//
// 	Generated string is "b", word becomes "ab".
// 	Generated string is "bc", word becomes "abbc".
// 	Generated string is "bccd", word becomes "abbcbccd".
//
// Constraints:
// 1 <= k <= 500
//
// Helpful references (internal KB):
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
//   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
//   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
//   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
//   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
// - Minimum stack / Minimum queue (queue, stack, simulation)
//   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
//   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
//   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
//   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
//   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char kthCharacter(int k) {
    int length = 1;  // Current length of the string
    int increment = 1;  // Incremental length added in each operation

    // Determine the length of the string after enough operations
    while (length < k) {
        increment++;
        length += increment;
    }

    // Backtrack to find the k-th character
    while (k > 1) {
        if (k > length - increment) {
            k -= (length - increment);
            k--;  // Move to the next character in the appended part
        }
        length -= increment;
        increment--;
    }

    return 'a' + (increment - 1);  // Calculate the character based on its position     
}
