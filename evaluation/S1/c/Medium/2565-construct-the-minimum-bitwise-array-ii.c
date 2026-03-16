// Source: https://leetcode.com/problems/construct-the-minimum-bitwise-array-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums consisting of n prime integers.
//
// You need to construct an array ans of length n, such that, for each index i, the bitwise OR of ans[i] and ans[i] + 1 is equal to nums[i], i.e. ans[i] OR (ans[i] + 1) == nums[i].
//
// Additionally, you must minimize each value of ans[i] in the resulting array.
//
// If it is not possible to find such a value for ans[i] that satisfies the condition, then set ans[i] = -1.
//
// Example:
// Input: nums = [2,3,5,7]
//
// Output: [-1,1,4,3]
//
// Explanation:
//
//
// 	For i = 0, as there is no value for ans[0] that satisfies ans[0] OR (ans[0] + 1) = 2, so ans[0] = -1.
// 	For i = 1, the smallest ans[1] that satisfies ans[1] OR (ans[1] + 1) = 3 is 1, because 1 OR (1 + 1) = 3.
// 	For i = 2, the smallest ans[2] that satisfies ans[2] OR (ans[2] + 1) = 5 is 4, because 4 OR (4 + 1) = 5.
// 	For i = 3, the smallest ans[3] that satisfies ans[3] OR (ans[3] + 1) = 7 is 3, because 3 OR (3 + 1) = 7.
//
// Constraints:
// 1 <= nums.length <= 100
// 	2 <= nums[i] <= 109
// 	nums[i] is a prime number.
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, bitset, sieve)
//   • When to use: When you need to find all prime numbers up to a certain limit N, or efficiently check primality for many numbers within that range. It is ideal for precomputing primes.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer N by iteratively marking multiples of each prime. It achieves O(N log log N) time complexity and O(N) space.
//   • Invariants: For any number i less than the current prime p, is_prime[i] correctly reflects its primality.; All multiples of primes smaller than the current prime p have already been marked as composite.
//   • Tips: Optimize by starting marking multiples from p*p for each prime p.; Use a bitset for memory efficiency when N is large.
//   • Pitfalls: Forgetting to explicitly handle 0 and 1 as non-prime.; Incorrectly marking multiples, e.g., starting from 2*p instead of p*p.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Minimum spanning tree - Prim's algorithm (graph, heap, array, mst-prim, greedy, heap-select)
//   • When to use: Use Prim's algorithm to find a minimum spanning tree in a connected, weighted graph. It is efficient for both dense graphs (O(V^2)) and sparse graphs (O(E log V)) depending on the implementation.
//   • Idea: Prim's algorithm is a greedy algorithm that builds an MST by iteratively adding the cheapest edge connecting a vertex in the growing tree to a vertex outside the tree. It has a time complexity of O(V^2) for dense graphs using an adjacency matrix or O(E log V) for sparse graphs using a priority queue.
//   • Invariants: All selected vertices and edges form a connected component of the final MST.; For any unselected vertex `v`, `min_e[v]` stores the minimum weight of an edge connecting `v` to the currently selected component.
//   • Tips: For dense graphs, an O(V^2) implementation using an an adjacency matrix and simple array scans is efficient.; For sparse graphs, use a priority queue (min-heap) with an adjacency list to achieve O(E log V) complexity.
//   • Pitfalls: Incorrectly updating the `min_e` array or priority queue entries can lead to an incorrect MST or performance issues.; Forgetting to mark vertices as 'selected' can lead to cycles or infinite loops.
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
int* minBitwiseArray(int* nums, int numsSize, int* returnSize) {
    int* ans = (int*)malloc(numsSize * sizeof(int));
    *returnSize = numsSize;

    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        // Since nums[i] is a prime number greater than 2, it is always odd.
        // The only case where ans[i] cannot be found is when nums[i] == 2.
        if (num == 2) {
            ans[i] = -1;
        } else {
            // For any odd prime number greater than 2, the minimum ans[i] can be found as follows:
            // ans[i] = nums[i] - 2
            ans[i] = num - 2;
        }
    }

    return ans;     
}
