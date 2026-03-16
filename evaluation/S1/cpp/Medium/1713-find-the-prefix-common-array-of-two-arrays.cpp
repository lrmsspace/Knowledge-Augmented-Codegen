// Source: https://leetcode.com/problems/find-the-prefix-common-array-of-two-arrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed integer permutations A and B of length n.
//
// A prefix common array of A and B is an array C such that C[i] is equal to the count of numbers that are present at or before the index i in both A and B.
//
// Return the prefix common array of A and B.
//
// A sequence of n integers is called a permutation if it contains all integers from 1 to n exactly once.
//
// Example:
// Input: A = [1,3,2,4], B = [3,1,2,4]
// Output: [0,2,3,4]
// Explanation: At i = 0: no number is common, so C[0] = 0.
// At i = 1: 1 and 3 are common in A and B, so C[1] = 2.
// At i = 2: 1, 2, and 3 are common in A and B, so C[2] = 3.
// At i = 3: 1, 2, 3, and 4 are common in A and B, so C[3] = 4.
//
// Constraints:
// 1 <= A.length == B.length == n <= 50
// 	1 <= A[i], B[i] <= n
// 	It is guaranteed that A and B are both a permutation of n integers.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Suffix Array (string, array, merge-sort)
//   • When to use: Use when needing to efficiently query properties of all suffixes or substrings of a given text, especially for pattern matching or finding repeated structures. It is particularly useful for problems requiring lexicographical ordering of all suffixes.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing their starting indices. It enables efficient string operations like pattern searching and finding longest common prefixes, typically constructed in O(N log N) time.
//   • Invariants: After k iterations, suffixes are sorted correctly up to a certain length (e.g., 2^k).; All suffixes of the original string are represented by their starting indices in the array.
//   • Tips: Append a unique sentinel character (e.g., '$') smaller than any other character to the string.; Utilize the LCP array, often built alongside, for advanced string queries and optimizations.
//   • Pitfalls: Naive sorting of suffixes by string comparison leads to an inefficient O(N^2 log N) complexity.; High memory usage for very long strings due to storing all suffixes implicitly or explicitly.
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It provides logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, also known as a Binary Indexed Tree (BIT), is a data structure that can efficiently update individual elements and calculate prefix sums in an array. Both operations are performed in O(log N) time.
//   • Invariants: Each `tree[i]` element stores the sum of a contiguous range of elements from the original array, specifically from `i - (i & -i) + 1` to `i` (inclusive, 1-based).; After any `update(idx, val)` operation, `query(idx)` will reflect the new sum up to `idx`.
//   • Tips: Use 1-based indexing for array elements to simplify bitwise logic; The `idx & -idx` operation is key to navigating the implicit tree structure
//   • Pitfalls: Confusing 0-based and 1-based indexing can lead to incorrect results; Off-by-one errors when calculating range sums (e.g., `query(R) - query(L-1)`)
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<int> posA(n + 1, 0), posB(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            posA[A[i]] = i;
            posB[B[i]] = i;
        }

        vector<int> C(n, 0);
        int commonCount = 0;
        vector<bool> seenA(n + 1, false), seenB(n + 1, false);
        for (int i = 0; i < n; ++i) {
            int aNum = A[i];
            int bNum = B[i];

            seenA[aNum] = true;
            seenB[bNum] = true;

            if (seenB[aNum]) {
                commonCount++;
            }
            if (aNum != bNum && seenA[bNum]) {
                commonCount++;
            }

            C[i] = commonCount;
        }

        return C;           
    }
};
