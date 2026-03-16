// Source: https://leetcode.com/problems/minimum-operations-to-make-array-elements-zero/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D array queries, where queries[i] is of the form [l, r]. Each queries[i] defines an array of integers nums consisting of elements ranging from l to r, both inclusive.
//
// In one operation, you can:
//
//
// 	Select two integers a and b from the array.
// 	Replace them with floor(a / 4) and floor(b / 4).
//
//
// Your task is to determine the minimum number of operations required to reduce all elements of the array to zero for each query. Return the sum of the results for all queries.
//
// Example:
// Input: queries = [[1,2],[2,4]]
//
// Output: 3
//
// Explanation:
//
// For queries[0]:
//
//
// 	The initial array is nums = [1, 2].
// 	In the first operation, select nums[0] and nums[1]. The array becomes [0, 0].
// 	The minimum number of operations required is 1.
//
//
// For queries[1]:
//
//
// 	The initial array is nums = [2, 3, 4].
// 	In the first operation, select nums[0] and nums[2]. The array becomes [0, 3, 1].
// 	In the second operation, select nums[1] and nums[2]. The array becomes [0, 0, 0].
// 	The minimum number of operations required is 2.
//
//
// The output is 1 + 2 = 3.
//
// Constraints:
// 1 <= queries.length <= 105
// 	queries[i].length == 2
// 	queries[i] == [l, r]
// 	1 <= l < r <= 109
//
// Helpful references (internal KB):
// - Sqrt Tree (array, tree, recursion)
//   • When to use: When you need to perform O(1) range queries and support efficient updates (single element or range) on an array, leveraging a hierarchical decomposition.
//   • Idea: A Sqrt Tree is a data structure that supports O(1) range queries and efficient updates on an array. It recursively decomposes the array into blocks and layers, using precomputed information and bitwise operations to quickly answer queries and propagate updates.
//   • Invariants: Each element is part of exactly one block at each layer of the Sqrt Tree.; The highest differing bit between `l` and `r` identifies the specific layer for processing `q(l, r)`.
//   • Tips: Precompute highest bit for efficient layer selection.; Decompose queries into intra-block and inter-block segments.
//   • Pitfalls: Naive updates can result in O(N) complexity per update.; High memory consumption due to multiple layers of precomputed arrays.
// - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
//   • When to use: Use when you need to perform O(1) range queries on a static array for an associative operation, after an O(N log N) preprocessing step.
//   • Idea: A data structure that precomputes answers for all possible range queries using an associative operation on a static array. It achieves O(1) query time and O(N log N) build time by storing prefix-like sums within logarithmically sized blocks.
//   • Invariants: For each level k, the array is partitioned into 2^k segments.; Within each segment, table[k][j] stores the result of the associative operation from j to the segment's midpoint (or midpoint to j).
//   • Tips: Ensure the operation is associative (e.g., min, max, sum, gcd, bitwise operations).; Preprocessing takes O(N log N) time and space.
//   • Pitfalls: Not suitable for mutable arrays; updates require rebuilding the table.; Requires O(N log N) memory, which can be substantial for very large N.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long minOperations(int** queries, int queriesSize, int* queriesColSize) {
    long long totalOperations = 0;

    for (int i = 0; i < queriesSize; i++) {
        int l = queries[i][0];
        int r = queries[i][1];
        long long operations = 0;

        // Calculate the number of operations needed for the range [l, r]
        while (l > 0 || r > 0) {
            // Perform one operation on the current range
            l /= 4;
            r /= 4;
            operations++;
        }

        totalOperations += operations;
    }

    return totalOperations;     
}
