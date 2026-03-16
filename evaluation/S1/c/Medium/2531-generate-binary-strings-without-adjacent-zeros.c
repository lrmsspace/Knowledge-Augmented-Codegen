// Source: https://leetcode.com/problems/generate-binary-strings-without-adjacent-zeros/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer n.
//
// A binary string x is valid if all substrings of x of length 2 contain at least one "1".
//
// Return all valid strings with length n, in any order.
//
// Example:
// Input: n = 3
//
// Output: ["010","011","101","110","111"]
//
// Explanation:
//
// The valid strings of length 3 are: "010", "011", "101", "110", and "111".
//
// Constraints:
// 1 <= n <= 18
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this algorithm to find the maximum length of a subsequence where elements are strictly increasing. It is particularly efficient when optimizing the O(N^2) dynamic programming solution to O(N log N) using binary search.
//   • Idea: This algorithm determines the longest subsequence of a given sequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search.
//   • Invariants: The 'tails' array always stores the smallest ending element for increasing subsequences of various lengths.; The 'tails' array is always sorted in strictly increasing order.
//   • Tips: The O(N log N) approach maintains an array 'tails' where 'tails[i]' is the smallest ending element of an increasing subsequence of length 'i+1'.; Utilize binary search (e.g., `std::lower_bound`) to find the correct position for the current element in the 'tails' array.
//   • Pitfalls: Confusing a subsequence with a contiguous subarray, which is a common mistake.; Incorrectly updating the 'tails' array, leading to non-increasing subsequences or incorrect lengths.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** validStrings(int n, int* returnSize) {
    // Calculate the maximum number of valid binary strings of length n
    // This is equivalent to the (n+2)th Fibonacci number
    int fib[n + 2];
    fib[0] = 1; // F(0)
    fib[1] = 1; // F(1)
    for (int i = 2; i <= n + 1; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    *returnSize = fib[n + 1];

    // Allocate memory for the result array
    char** result = (char**)malloc((*returnSize) * sizeof(char*));
    for (int i = 0; i < *returnSize; i++) {
        result[i] = (char*)malloc((n + 1) * sizeof(char));
        result[i][n] = '\0'; // Null-terminate each string
    }

    // Helper function to generate valid strings using backtracking
    void backtrack(int pos, char* current, int* index) {
        if (pos == n) {
            // Copy the current valid string to the result array
            for (int i = 0; i < n; i++) {
                result[*index][i] = current[i];
            }
            (*index)++;
            return;
        }

        // Place '1' at the current position
        current[pos] = '1';
        backtrack(pos + 1, current, index);

        // Place '0' at the current position only if the previous character is not '0'
        if (pos == 0 || current[pos - 1] != '0') {
            current[pos] = '0';
            backtrack(pos + 1, current, index);
        }
    }

    // Start backtracking from position 0
    char current[n + 1];
    int index = 0;
    backtrack(0, current, &index);

    return result;      
}
