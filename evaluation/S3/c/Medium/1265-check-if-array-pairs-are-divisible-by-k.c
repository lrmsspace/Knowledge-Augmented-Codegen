// Source: https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers arr of even length n and an integer k.
//
// We want to divide the array into exactly n / 2 pairs such that the sum of each pair is divisible by k.
//
// Return true If you can find a way to do that or false otherwise.
//
// Example:
// Input: arr = [1,2,3,4,5,10,6,7,8,9], k = 5
// Output: true
// Explanation: Pairs are (1,9),(2,8),(3,7),(4,6) and (5,10).
//
// Constraints:
// arr.length == n
// 	1 <= n <= 105
// 	n is even.
// 	-109 <= arr[i] <= 109
// 	1 <= k <= 105
//
// Helpful references (internal KB):
// - Burnside's lemma / Pólya enumeration theorem (array, number, enumeration, simulation)
//   • When to use: Use when counting the number of distinct configurations or arrangements of objects under a set of symmetry operations, where configurations are considered identical if one can be transformed into another by a group action.
//   • Idea: Burnside's Lemma and Pólya Enumeration Theorem are combinatorial tools used to count the number of distinct objects under a group of symmetries. Both typically involve iterating through group elements and analyzing permutation cycle structures, often resulting in polynomial time complexity depending on group size and element analysis.
//   • Invariants: The set of group elements considered remains consistent throughout the summation.; Each group element's cycle decomposition is correctly identified.
//   • Tips: Identify the group of symmetry operations acting on the objects.; For each group element, determine its permutation cycle structure.
//   • Pitfalls: Incorrectly identifying the full set of distinct group operations.; Errors in determining the cycle structure of permutations.
// - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
//   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
//   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
//   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
//   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
//   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
// - Reservoir Sampling (array, randomized, simulation)
//   • When to use: When you need to randomly select a fixed number of items (k) from a stream or a very large dataset of unknown size, ensuring each item has an equal probability of selection in a single pass.
//   • Idea: Reservoir sampling is a randomized algorithm that selects k items from a list containing n items, where n is either a very large or unknown number, ensuring each item has an equal probability of being selected. It processes the input in a single pass with O(N) time complexity and O(k) space complexity.
//   • Invariants: The reservoir always contains exactly k elements.; Any element processed up to the current index `i` has a k/(i+1) probability of being in the reservoir.
//   • Tips: Initialize the reservoir with the first k elements from the stream.; For each subsequent element, generate a random index from 0 to current_stream_index.
//   • Pitfalls: Failing to correctly initialize the reservoir with the first k elements.; Generating random indices outside the valid range [0, current_stream_index] or [0, k-1].
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool canArrange(int* arr, int arrSize, int k) {
    int count[k];
    memset(count, 0, sizeof(count));

    for (int i = 0; i < arrSize; i++) {
        int rem = ((arr[i] % k) + k) % k; // Handle negative numbers
        count[rem]++;
    }

    if (count[0] % 2 != 0) {
        return false; // Pairs of elements that are divisible by k must be even
    }

    for (int i = 1; i < (k + 1) / 2; i++) {
        if (count[i] != count[k - i]) {
            return false; // Pairs of elements with remainders i and k-i must match
        }
    }

    if (k % 2 == 0 && count[k / 2] % 2 != 0) {
        return false; // If k is even, pairs of elements with remainder k/2 must be even
    }

    return true;        
}
