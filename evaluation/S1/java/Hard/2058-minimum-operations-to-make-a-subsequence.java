// Source: https://leetcode.com/problems/minimum-operations-to-make-a-subsequence/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array target that consists of distinct integers and another integer array arr that can have duplicates.
//
// In one operation, you can insert any integer at any position in arr. For example, if arr = [1,4,1,2], you can add 3 in the middle and make it [1,4,3,1,2]. Note that you can insert the integer at the very beginning or end of the array.
//
// Return the minimum number of operations needed to make target a subsequence of arr.
//
// A subsequence of an array is a new array generated from the original array by deleting some elements (possibly none) without changing the remaining elements' relative order. For example, [2,7,4] is a subsequence of [4,2,3,7,2,1,4] (the underlined elements), while [2,4,2] is not.
//
// Example:
// Input: target = [5,1,3], arr = [9,4,2,3,4]
// Output: 2
// Explanation: You can add 5 and 1 in such a way that makes arr = [5,9,4,1,2,3,4], then target will be a subsequence of arr.
//
// Constraints:
// 1 <= target.length, arr.length <= 105
// 	1 <= target[i], arr[i] <= 109
// 	target contains no duplicates.
//
// Helpful references (internal KB):
// - Longest Increasing Subsequence (array, dp-1d, binary-search)
//   • When to use: Use when you need to find the longest possible subsequence of a given sequence such that elements in the subsequence are in strictly increasing order. It is often applied to optimization problems involving ordered subsets.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence where all elements are sorted in increasing order. It can be solved in O(N log N) time using dynamic programming with binary search optimization, or O(N^2) using basic DP.
//   • Invariants: The 'tails' array always stores the smallest ending element for all increasing subsequences of a given length.; The 'tails' array remains sorted in strictly increasing order throughout the algorithm's execution.
//   • Tips: The O(N log N) approach uses a 'tails' array to store the smallest tail of all increasing subsequences of length 'i+1'.; Binary search is crucial for efficiently finding the correct position for the current element in the 'tails' array.
//   • Pitfalls: Confusing subsequence with contiguous subarray or substring.; Incorrectly updating or searching in the 'tails' array, leading to wrong lengths or values.
// - Hash Tables (array, number, string, hashing)
//   • When to use: Use when you need to store and retrieve key-value pairs efficiently by transforming keys into array indices, managing potential collisions.
//   • Idea: Hash tables map keys to array indices using a hash function, enabling average O(1) time complexity for insertions, deletions, and lookups by efficiently managing potential collisions.
//   • Invariants: The hash function always produces an index within the valid array bounds [0, M-1].; For any two equal keys, their hash values remain identical.
//   • Tips: Design hash functions for uniform key distribution across the array.; Ensure hash functions are deterministic and efficient to compute.
//   • Pitfalls: Using a hash function that does not uniformly distribute keys, leading to many collisions.; Failing to implement a proper collision resolution strategy.
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when performing many range queries on a static array where the query operation is idempotent (e.g., min, max, GCD) to achieve O(1) query time after O(N log N) precomputation.
//   • Idea: A data structure that precomputes answers for all possible range queries of power-of-two lengths, allowing O(1) query time for idempotent operations like range minimum/maximum queries. Precomputation takes O(N log N) time and space.
//   • Invariants: The `st[k][i]` entry stores the result of the operation for the range `[i, i + 2^k - 1]`.; All ranges of length `2^k` starting at `i` are correctly computed in `st[k][i]` during precomputation.
//   • Tips: Precompute logarithms for O(1) lookup of `floor(log2(length))` during queries.; Sparse tables are most efficient for idempotent operations (min, max, GCD, OR, AND) due to overlapping segments.
//   • Pitfalls: Not suitable for dynamic arrays or scenarios requiring updates, as modifications invalidate the precomputed table.; High memory usage: requires O(N log N) space, which can be significant for large N.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minOperations(int[] target, int[] arr) {
        // Map each value in target to its index
        Map<Integer, Integer> indexMap = new HashMap<>();
        for (int i = 0; i < target.length; i++) {
            indexMap.put(target[i], i);
        }

        // Transform arr into a sequence of indices based on target
        List<Integer> transformed = new ArrayList<>();
        for (int num : arr) {
            if (indexMap.containsKey(num)) {
                transformed.add(indexMap.get(num));
            }
        }

        // Find the length of the Longest Increasing Subsequence (LIS) in transformed
        return target.length            
    }
}
