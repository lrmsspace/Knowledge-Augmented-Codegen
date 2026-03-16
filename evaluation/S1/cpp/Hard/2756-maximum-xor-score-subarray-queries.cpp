// Source: https://leetcode.com/problems/maximum-xor-score-subarray-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums of n integers, and a 2D integer array queries of size q, where queries[i] = [li, ri].
//
// For each query, you must find the maximum XOR score of any subarray of nums[li..ri].
//
// The XOR score of an array a is found by repeatedly applying the following operations on a so that only one element remains, that is the score:
//
//
// 	Simultaneously replace a[i] with a[i] XOR a[i + 1] for all indices i except the last one.
// 	Remove the last element of a.
//
//
// Return an array answer of size q where answer[i] is the answer to query i.
//
// Example:
// Input: nums = [2,8,4,32,16,1], queries = [[0,2],[1,4],[0,5]]
//
// Output: [12,60,60]
//
// Explanation:
//
// In the first query, nums[0..2] has 6 subarrays [2], [8], [4], [2, 8], [8, 4], and [2, 8, 4] each with a respective XOR score of 2, 8, 4, 10, 12, and 6. The answer for the query is 12, the largest of all XOR scores.
//
// In the second query, the subarray of nums[1..4] with the largest XOR score is nums[1..4] with a score of 60.
//
// In the third query, the subarray of nums[0..5] with the largest XOR score is nums[1..4] with a score of 60.
//
// Constraints:
// 1 <= n == nums.length <= 2000
// 	0 <= nums[i] <= 231 - 1
// 	1 <= q == queries.length <= 105
// 	queries[i].length == 2 
// 	queries[i] = [li, ri]
// 	0 <= li <= ri <= n - 1
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Sqrt Tree (array, tree, recursion)
//   • When to use: When you need to perform O(1) range queries and support efficient updates (single element or range) on an array, leveraging a hierarchical decomposition.
//   • Idea: A Sqrt Tree is a data structure that supports O(1) range queries and efficient updates on an array. It recursively decomposes the array into blocks and layers, using precomputed information and bitwise operations to quickly answer queries and propagate updates.
//   • Invariants: Each element is part of exactly one block at each layer of the Sqrt Tree.; The highest differing bit between `l` and `r` identifies the specific layer for processing `q(l, r)`.
//   • Tips: Precompute highest bit for efficient layer selection.; Decompose queries into intra-block and inter-block segments.
//   • Pitfalls: Naive updates can result in O(N) complexity per update.; High memory consumption due to multiple layers of precomputed arrays.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> maximumSubarrayXor(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> prefixXor(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixXor[i + 1] = prefixXor[i] ^ nums[i];
        }

        vector<int> results;
        for (const auto& query : queries) {
            int l = query[0];
            int r = query[1];
            int maxXor = 0;
            for (int start = l; start <= r; ++start) {
                for (int end = start; end <= r; ++end) {
                    int currentXor = prefixXor[end + 1] ^ prefixXor[start];
                    maxXor = max(maxXor, currentXor);
                }
            }
            results.push_back(maxXor);
        }

        return results;         
    }
};
