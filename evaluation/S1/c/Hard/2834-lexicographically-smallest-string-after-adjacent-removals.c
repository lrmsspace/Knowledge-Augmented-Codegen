// Source: https://leetcode.com/problems/lexicographically-smallest-string-after-adjacent-removals/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s consisting of lowercase English letters.
//
// You can perform the following operation any number of times (including zero):
//
//
// 	Remove any pair of adjacent characters in the string that are consecutive in the alphabet, in either order (e.g., 'a' and 'b', or 'b' and 'a').
// 	Shift the remaining characters to the left to fill the gap.
//
//
// Return the lexicographically smallest string that can be obtained after performing the operations optimally.
//
// Note: Consider the alphabet as circular, thus 'a' and 'z' are consecutive.
//
// Example:
// Input: s = "abc"
//
// Output: "a"
//
// Explanation:
//
//
// 	Remove "bc" from the string, leaving "a" as the remaining string.
// 	No further operations are possible. Thus, the lexicographically smallest string after all possible removals is "a".
//
// Constraints:
// 1 <= s.length <= 250
// 	s consists only of lowercase English letters.
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

char* lexicographicallySmallestString(char* s) {
    int len = strlen(s);
    char* stack = (char*)malloc((len + 1) * sizeof(char));
    int top = -1;

    for (int i = 0; i < len; i++) {
        char current = s[i];
        while (top >= 0) {
            char topChar = stack[top];
            if ((topChar == current + 1) || (topChar == current - 1) ||
                (topChar == 'a' && current == 'z') || (topChar == 'z' && current == 'a')) {
                top--; // Pop the top character
                current = '\0'; // Mark current as removed
            } else {
                break;
            }
        }
        if (current != '\0') {
            stack[++top] = current; // Push current character onto the stack
        }
    }

    stack[top + 1] = '\0'; // Null-terminate the resulting string
    return stack;       
}
