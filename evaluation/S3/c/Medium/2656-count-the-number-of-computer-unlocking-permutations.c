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
// - Prüfer code (tree, heap, simulation, greedy)
//   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
//   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
//   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
//   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
//   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
// - Prüfer code (tree, heap, simulation, greedy)
//   • When to use: Use when counting labeled trees or converting between a labeled tree and a unique sequence representation for combinatorial analysis. It provides a bijection for problems involving N labeled nodes.
//   • Idea: Prüfer code is a unique sequence of length N-2 that represents a labeled tree with N nodes. It is constructed by iteratively removing the smallest-labeled leaf and recording its neighbor, and can be reconstructed back into the tree.
//   • Invariants: The Prüfer sequence always contains N-2 elements for a tree with N nodes.; At each step of encoding, the removed node is a leaf with the smallest label among all current leaves.
//   • Tips: Maintain an array of node degrees for efficient updates.; Use a min-priority queue to quickly find the smallest-labeled leaf.
//   • Pitfalls: Incorrectly updating node degrees after removal.; Off-by-one errors when dealing with 0-indexed vs. 1-indexed labels.
// - Longest Increasing Subsequence (array, coordinate-compress, segment-tree, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements must be strictly increasing. It is applicable for problems requiring optimal substructure on sequences with an increasing property.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements of the subsequence are in increasing order. It can be solved in O(N log N) time using dynamic programming with binary search or a segment tree with coordinate compression.
//   • Invariants: The `dp` array (or segment tree) stores information about the smallest ending element for increasing subsequences of various lengths.; The `dp` array, if used, remains sorted in strictly increasing order.
//   • Tips: The O(N log N) solution uses a `dp` array storing the smallest ending element for all increasing subsequences of a given length.; Binary search (`lower_bound`) efficiently finds the correct position to update in the `dp` array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates; LIS typically requires strictly increasing elements.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countPermutations(int* complexity, int complexitySize) {
    // The number of valid permutations corresponds to the number of labeled trees that can be formed with the given complexities as node labels.
    // We can use Prüfer code to count the number of such trees.
    // The number of labeled trees with n nodes is n^(n-2) according to Cayley's formula.

    const int MOD = 1000000007;
    long long result = 1;
    
    // Calculate n^(n-2) % MOD
    for (int i = 0; i < complexitySize - 2; i++) {
        result = (result * complexitySize) % MOD;
    }
    
    return (int)result;     
}
