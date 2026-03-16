// Source: https://leetcode.com/problems/maximize-ysum-by-picking-a-triplet-of-distinct-xvalues/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays x and y, each of length n. You must choose three distinct indices i, j, and k such that:
//
//
// 	x[i] != x[j]
// 	x[j] != x[k]
// 	x[k] != x[i]
//
//
// Your goal is to maximize the value of y[i] + y[j] + y[k] under these conditions. Return the maximum possible sum that can be obtained by choosing such a triplet of indices.
//
// If no such triplet exists, return -1.
//
// Example:
// Input: x = [1,2,1,3,2], y = [5,3,4,6,2]
//
// Output: 14
//
// Explanation:
//
//
// 	Choose i = 0 (x[i] = 1, y[i] = 5), j = 1 (x[j] = 2, y[j] = 3), k = 3 (x[k] = 3, y[k] = 6).
// 	All three values chosen from x are distinct. 5 + 3 + 6 = 14 is the maximum we can obtain. Hence, the output is 14.
//
// Constraints:
// n == x.length == y.length
// 	3 <= n <= 105
// 	1 <= x[i], y[i] <= 106
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - bucket-sort (array, bucket-sort)
//   • When to use: Use when sorting elements with a known, uniform distribution over a specific range. It is efficient for numbers that are uniformly distributed across a range, often achieving linear time complexity.
//   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually, and then concatenates them. It can achieve O(N+K) average time complexity for uniformly distributed data.
//   • Invariants: After distributing elements, each element `x` is in bucket `floor(N * x)`.; After sorting buckets, every bucket `buckets[i]` contains its elements in sorted order.
//   • Tips: Choose the number of buckets appropriately based on data distribution and range.; Normalize input data to a [0, 1) range for simpler bucket indexing.
//   • Pitfalls: Poor performance with non-uniform data distribution, potentially degrading to O(N^2).; Requires extra space for the buckets, proportional to N+K.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxSumDistinctTriplet(int* x, int xSize, int* y, int ySize) {
    // Create an array of pairs (x[i], y[i])
    typedef struct {
        int x;
        int y;
    } Pair;

    Pair* pairs = (Pair*)malloc(xSize * sizeof(Pair));
    for (int i = 0; i < xSize; i++) {
        pairs[i].x = x[i];
        pairs[i].y = y[i];
    }

    // Sort pairs by y in descending order
    int compare(const void* a, const void* b) {
        return ((Pair*)b)->y - ((Pair*)a)->y;
    }
    qsort(pairs, xSize, sizeof(Pair), compare);

    int distinctCount = 0;
    int sum = 0;
    int lastX = -1;

    // Iterate through sorted pairs and pick distinct x values
    for (int i = 0; i < xSize && distinctCount < 3; i++) {
        if (pairs[i].x != lastX) {
            sum += pairs[i].y;
            lastX = pairs[i].x;
            distinctCount++;
        }
    }

    free(pairs);

    return (distinctCount == 3) ? sum : -1;     
}
