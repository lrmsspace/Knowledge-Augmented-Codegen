// Source: https://leetcode.com/problems/beautiful-array/   |   Difficulty: Medium
//
// Problem Description:
// An array nums of length n is beautiful if:
//
//
// 	nums is a permutation of the integers in the range [1, n].
// 	For every 0 <= i < j < n, there is no index k with i < k < j where 2 * nums[k] == nums[i] + nums[j].
//
//
// Given the integer n, return any beautiful array nums of length n. There will be at least one valid answer for the given n.
//
// Example:
// Input: n = 4
// Output: [2,1,4,3]
//
// Constraints:
// 1 <= n <= 1000
//
// Helpful references (internal KB):
// - Fast Fourier transform (array, divide-and-conquer, recursion)
//   • When to use: Use when performing fast polynomial multiplication, large number multiplication, or general convolutions, especially when an O(N log N) time complexity is required for large inputs.
//   • Idea: The Fast Fourier Transform (FFT) is an algorithm that computes the Discrete Fourier Transform (DFT) and its inverse in O(N log N) time. It leverages a divide-and-conquer strategy to efficiently transform a polynomial's coefficients to its point-value representation and vice-versa.
//   • Invariants: At the start of each recursive call, the input array length N is a power of two.; The DFT of the current polynomial is correctly computed from the DFTs of its even and odd coefficient sub-polynomials.
//   • Tips: Pad polynomials with zeros to a power-of-two length for efficient processing.; Use complex numbers for roots of unity, or modular arithmetic for Number Theoretic Transform (NTT).
//   • Pitfalls: Forgetting to pad polynomials to a sufficient degree (sum of degrees) for multiplication.; Numerical precision issues when using floating-point complex numbers for large N.
// - Sqrt Tree (array, tree, recursion, simulation)
//   • When to use: Use for efficient range queries on an array, achieving very low query complexity by leveraging a hierarchical block decomposition and specific structural properties like power-of-two block sizes.
//   • Idea: A Sqrt Tree is a hierarchical data structure designed for answering range queries on an array, achieving O(log log n) or better query time by recursively decomposing the array into blocks and layers.
//   • Invariants: Each layer of the Sqrt Tree consists of segments of equal length.; All blocks within a given layer have an equal, power-of-two size.
//   • Tips: Pad the input array with dummy elements to ensure its size is a power of two for simplified block calculations.; Ensure all block sizes on each layer are powers of two to enable efficient binary representation tricks for queries.
//   • Pitfalls: Incorrectly calculating block boundaries or segment sizes, leading to off-by-one errors or out-of-bounds access.; Overlooking the memory overhead associated with storing precomputed values for all blocks across multiple layers.
// - Josephus Problem (number, recursion, counting)
//   • When to use: Use when simulating a circular elimination process with a fixed step size, especially when seeking the survivor's position. It's particularly efficient for specific step sizes like two.
//   • Idea: The Josephus Problem determines the last remaining position in a circular arrangement after elements are eliminated at fixed intervals. The recursive solution for a step size of two has a logarithmic time complexity, O(log N), due to its divide-and-conquer nature.
//   • Invariants: The number of participants N is always positive in each recursive subproblem.; The returned position is always within the valid range [0, current N-1] (or [1, current N]).
//   • Tips: Base cases are crucial for recursive solutions, typically for N=1.; Observe patterns for specific step sizes, especially k=2, which has a simpler formula.
//   • Pitfalls: Off-by-one errors when converting between 0-indexed and 1-indexed results.; Incorrectly applying the position 'shift' after elements are eliminated in subproblems.
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
int* beautifulArray(int n, int* returnSize) {
    int* res = (int*)malloc(n * sizeof(int));
    *returnSize = n;
    for (int i = 0; i < n; i++) {
        res[i] = i + 1;
    }

    int* temp = (int*)malloc(n * sizeof(int));
    int size = n, tempSize;

    while (size > 1) {
        tempSize = 0;
        for (int i = 0; i < size; i++) {
            if (res[i] % 2 == 1) {
                temp[tempSize++] = res[i];
            }
        }
        for (int i = 0; i < size; i++) {
            if (res[i] % 2 == 0) {
                temp[tempSize++] = res[i];
            }
        }
        memcpy(res, temp, tempSize * sizeof(int));
        size = tempSize;
    }

    free(temp);
    return res;     
}
