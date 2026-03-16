// Source: https://leetcode.com/problems/count-the-number-of-computer-unlocking-permutations/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array complexity of length n.
//
// There are n locked computers in a room with labels from 0 to n - 1, each with its own unique password. The password of the computer i has a complexity complexity[i].
//
// The password for the computer labeled 0 is already decrypted and serves as the root. All other computers must be unlocked using it or another previously unlocked computer, following this information:
//
//
//  You can decrypt the password for the computer i using the password for computer j, where j is any integer less than i with a lower complexity. (i.e. j < i and complexity[j] < complexity[i])
//  To decrypt the password for computer i, you must have already unlocked a computer j such that j < i and complexity[j] < complexity[i].
//
//
// Find the number of permutations of [0, 1, 2, ..., (n - 1)] that represent a valid order in which the computers can be unlocked, starting from computer 0 as the only initially unlocked one.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Note that the password for the computer with label 0 is decrypted, and not the computer with the first position in the permutation.
//
// Example:
// Input: complexity = [1,2,3]
//
// Output: 2
//
// Explanation:
//
// The valid permutations are:
//
//
//  [0, 1, 2]
//  
//   Unlock computer 0 first with root password.
//   Unlock computer 1 with password of computer 0 since complexity[0] < complexity[1].
//   Unlock computer 2 with password of computer 1 since complexity[1] < complexity[2].
//  
//  
//  [0, 2, 1]
//  
//   Unlock computer 0 first with root password.
//   Unlock computer 2 with password of computer 0 since complexity[0] < complexity[2].
//   Unlock computer 1 with password of computer 0 since complexity[0] < complexity[1].
//
// Constraints:
// 2 <= complexity.length <= 105
//  1 <= complexity[i] <= 109
//
// Helpful references (internal KB):
// - Longest Increasing Subsequence (array, coordinate-compress, segment-tree, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements must be strictly increasing. It is applicable for problems requiring optimal substructure on sequences with an increasing property.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements of the subsequence are in increasing order. It can be solved in O(N log N) time using dynamic programming with binary search or a segment tree with coordinate compression.
//   • Invariants: The `dp` array (or segment tree) stores information about the smallest ending element for increasing subsequences of various lengths.; The `dp` array, if used, remains sorted in strictly increasing order.
//   • Tips: The O(N log N) solution uses a `dp` array storing the smallest ending element for all increasing subsequences of a given length.; Binary search (`lower_bound`) efficiently finds the correct position to update in the `dp` array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates; LIS typically requires strictly increasing elements.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countPermutations(int* complexity, int complexitySize) {
    // This problem can be solved using the concept of counting labeled trees, specifically using Prüfer code.
    // The number of valid permutations corresponds to the number of ways to construct a tree with n vertices where the degree of each vertex is determined by the complexity values.

    // Step 1: Count the degree of each vertex based on the complexity values.
    int* degree = (int*)calloc(complexitySize, sizeof(int));
    for (int i = 0; i < complexitySize; i++) {
        for (int j = 0; j < i; j++) {
            if (complexity[j] < complexity[i]) {
                degree[i]++;
            }
        }
    }

    // Step 2: The number of valid permutations is given by the formula:
    // Number of trees with n vertices and degree sequence d1, d2, ..., dn is:
    // (n-2)! / (d1! * d2! * ... * dn!)
    long long result = 1;
    long long factorial = 1;
    for (int i = 0; i < complexitySize; i++) {
        factorial = (factorial * (i + 1)) % 1000000007;
        result = (result * factorial) % 1000000007;
        for (int j = 0; j < degree[i]; j++) {
            result = (result * modInverse(j + 1, 1000000007)) % 1000000007;
        }
    }

    free(degree);
    return result;      
}
