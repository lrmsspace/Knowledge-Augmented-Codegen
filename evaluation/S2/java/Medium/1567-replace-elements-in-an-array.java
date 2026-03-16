// Source: https://leetcode.com/problems/replace-elements-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums that consists of n distinct positive integers. Apply m operations to this array, where in the ith operation you replace the number operations[i][0] with operations[i][1].
//
// It is guaranteed that in the ith operation:
//
//
// 	operations[i][0] exists in nums.
// 	operations[i][1] does not exist in nums.
//
//
// Return the array obtained after applying all the operations.
//
// Example:
// Input: nums = [1,2,4,6], operations = [[1,3],[4,7],[6,1]]
// Output: [3,2,7,1]
// Explanation: We perform the following operations on nums:
// - Replace the number 1 with 3. nums becomes [3,2,4,6].
// - Replace the number 4 with 7. nums becomes [3,2,7,6].
// - Replace the number 6 with 1. nums becomes [3,2,7,1].
// We return the final array [3,2,7,1].
//
// Constraints:
// n == nums.length
// 	m == operations.length
// 	1 <= n, m <= 105
// 	All the values of nums are distinct.
// 	operations[i].length == 2
// 	1 <= nums[i], operations[i][0], operations[i][1] <= 106
// 	operations[i][0] will exist in nums when applying the ith operation.
// 	operations[i][1] will not exist in nums when applying the ith operation.
//
// Helpful references (internal KB):
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It provides logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, also known as a Binary Indexed Tree (BIT), is a data structure that can efficiently update individual elements and calculate prefix sums in an array. Both operations are performed in O(log N) time.
//   • Invariants: Each `tree[i]` element stores the sum of a contiguous range of elements from the original array, specifically from `i - (i & -i) + 1` to `i` (inclusive, 1-based).; After any `update(idx, val)` operation, `query(idx)` will reflect the new sum up to `idx`.
//   • Tips: Use 1-based indexing for array elements to simplify bitwise logic; The `idx & -idx` operation is key to navigating the implicit tree structure
//   • Pitfalls: Confusing 0-based and 1-based indexing can lead to incorrect results; Off-by-one errors when calculating range sums (e.g., `query(R) - query(L-1)`)
// - Lowest Common Ancestor - Tarjan's off-line algorithm (tree, ds, dfs, union-find)
//   • When to use: Use when you need to find the Lowest Common Ancestor for multiple pairs of nodes in a tree, and all queries are known beforehand. It's an efficient offline approach for batch processing LCA queries.
//   • Idea: Tarjan's offline LCA algorithm uses a Depth-First Search (DFS) traversal combined with a Union-Find data structure to answer all LCA queries efficiently. It processes N nodes and Q queries in O(N + Q * alpha(N)) time, where alpha is the inverse Ackermann function.
//   • Invariants: After visiting a node 'u' and all its children, 'u' is marked as visited.; For any node 'v' whose subtree has been fully processed, 'find_set(v)' returns the representative of 'v''s component.
//   • Tips: Mark nodes as visited during DFS to track processed subtrees.; Use Union-Find's union operation to merge child subtrees with their parent after processing.
//   • Pitfalls: Forgetting to mark nodes as visited, leading to incorrect LCA identification.; Incorrectly updating the 'ancestor' array or 'find_set' logic in Union-Find.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] arrayChange(int[] nums, int[][] operations) {
        // Create a mapping from current values to their indices for O(1) access
        Map<Integer, Integer> valueToIndex = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            valueToIndex.put(nums[i], i);
        }

        // Process each operation
        for (int[] operation : operations) {
            int oldValue = operation[0];
            int newValue = operation[1];

            // Get the index of the old value
            int index = valueToIndex.get(oldValue);

            // Update the array with the new value
            nums[index] = newValue;

            // Update the mapping with the new value and remove the old value
            valueToIndex.remove(oldValue);
            valueToIndex.put(newValue, index);
        }

        return nums;            
    }
}
