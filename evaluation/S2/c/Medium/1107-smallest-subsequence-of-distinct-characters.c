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
// - Data Compression (tree, heap, greedy, recursion, counting)
//   • When to use: Use when you need to losslessly compress data by assigning shorter bit sequences to more frequent symbols, aiming for the shortest possible average code length. It is effective for data with non-uniform character distributions.
//   • Idea: Huffman coding is a greedy algorithm that constructs an optimal prefix code for a given set of symbols and their frequencies. It builds a binary tree (Huffman trie) by repeatedly merging the two nodes with the smallest frequencies, resulting in an encoding with O(N + K log K) time complexity, where N is input length and K is alphabet size.
//   • Invariants: The priority queue always contains valid Huffman nodes, each representing a subtree or a leaf character.; Every internal node in the Huffman tree has exactly two children, and its frequency is the sum of its children's frequencies.
//   • Tips: Use a min-priority queue to efficiently retrieve and combine the two lowest-frequency nodes.; Represent the Huffman tree explicitly to generate codes and for decoding.
//   • Pitfalls: The overhead of storing the Huffman tree or frequency table can negate compression benefits for small inputs.; Not truly optimal for all data types; it's a statistical compression method.
// - Minimum stack / Minimum queue (queue, deque, monotonic-queue)
//   • When to use: Use this technique when you need to perform standard queue or stack operations while also querying the minimum (or maximum) element in O(1) time. It is ideal for problems involving sliding windows or dynamic collections where min/max queries are frequent.
//   • Idea: This technique augments a queue or stack with an auxiliary data structure, typically a deque, to maintain elements in monotonic order. This allows for O(1) retrieval of the minimum (or maximum) element, with standard operations achieving amortized O(1) time complexity.
//   • Invariants: The auxiliary deque stores elements in non-decreasing order from front to back.; The element at the front of the auxiliary deque is the minimum of all elements currently in the main queue/stack.
//   • Tips: Utilize a deque for the auxiliary structure to efficiently add and remove from both ends.; For a minimum queue, maintain the auxiliary deque in non-decreasing order from front to back.
//   • Pitfalls: Incorrectly handling removals when the element to be removed from the main structure is not the current minimum.; Forgetting to remove elements from the auxiliary deque when they are no longer relevant (e.g., out of window bounds).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* smallestSubsequence(char* s) {
    int last_occurrence[26] = {0}; // Store the last occurrence index of each character
    int visited[26] = {0}; // Track if a character is included in the result
    int length = 0; // Length of the input string

    // Calculate the last occurrence of each character
    for (int i = 0; s[i] != '\0'; i++) {
        last_occurrence[s[i] - 'a'] = i;
        length++;
    }

    char* stack = (char*)malloc((length + 1) * sizeof(char)); // Stack to build the result
    int top = -1; // Stack pointer

    for (int i = 0; s[i] != '\0'; i++) {
        int index = s[i] - 'a';

        // If the character is already included in the result, skip it
        if (visited[index]) {
            continue;
        }

        // Pop characters from the stack if they are greater than the current character
        // and if they will appear again later in the string
        while (top >= 0 && stack[top] > s[i] && last_occurrence[stack[top] - 'a'] > i) {
            visited[stack[top] - 'a'] = 0; // Mark as not visited
            top--; // Pop from stack
        }

        // Push the current character onto the stack and mark it as visited
        stack[++top] = s[i];
        visited[index] = 1;
    }

    stack[top + 1] = '\0'; // Null-terminate the result string
    return stack;       
}
