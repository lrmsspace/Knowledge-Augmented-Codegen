// Source: https://leetcode.com/problems/closest-equal-element-queries/   |   Difficulty: Medium
//
// Problem Description:
// You are given a circular array nums and an array queries.
//
// For each query i, you have to find the following:
//
//
// 	The minimum distance between the element at index queries[i] and any other index j in the circular array, where nums[j] == nums[queries[i]]. If no such index exists, the answer for that query should be -1.
//
//
// Return an array answer of the same size as queries, where answer[i] represents the result for query i.
//
// Example:
// Input: nums = [1,3,1,4,1,3,2], queries = [0,3,5]
//
// Output: [2,-1,3]
//
// Explanation:
//
//
// 	Query 0: The element at queries[0] = 0 is nums[0] = 1. The nearest index with the same value is 2, and the distance between them is 2.
// 	Query 1: The element at queries[1] = 3 is nums[3] = 4. No other index contains 4, so the result is -1.
// 	Query 2: The element at queries[2] = 5 is nums[5] = 3. The nearest index with the same value is 1, and the distance between them is 3 (following the circular path: 5 -> 6 -> 0 -> 1).
//
// Constraints:
// 1 <= queries.length <= nums.length <= 105
// 	1 <= nums[i] <= 106
// 	0 <= queries[i] < nums.length
//
// Helpful references (internal KB):
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when you need to perform many range queries on a static array, especially when the query operation is associative and idempotent, allowing for O(1) query time after O(N log N) precomputation.
//   • Idea: A Sparse Table is a data structure that precomputes answers for all possible range queries of power-of-two lengths. It allows O(1) query time for idempotent operations like min/max/gcd and O(log N) for non-idempotent associative operations, after an O(N log N) build time.
//   • Invariants: After precomputation, dp[k][i] stores the result for the range [i, i + 2^k - 1].; For any k > 0, dp[k][i] is the result of combining dp[k-1][i] and dp[k-1][i + 2^(k-1)].
//   • Tips: Precompute log2 values for faster range length calculations.; Store dp[k][i] as the result for range [i, i + 2^k - 1].
//   • Pitfalls: Does not support updates to array elements efficiently.; Requires O(N log N) space, which can be significant for large N.
// - String Hashing (string, number, hashing)
//   • When to use: Use when needing to compare strings or substrings quickly, reducing comparison time from linear to constant. It is ideal for problems requiring frequent string equality checks or pattern matching across large texts.
//   • Idea: String hashing maps a string to an integer hash value, allowing for O(1) equality checks between strings or substrings. This technique relies on a hash function where equal strings must produce equal hashes, though the reverse is not guaranteed.
//   • Invariants: The hash of any prefix s[0...i] is correctly computed based on s[0...i-1] and s[i].; All characters processed up to the current index i contribute to the current hash value.
//   • Tips: Use a polynomial rolling hash function with a prime base and a large prime modulus.; Employ double hashing (two different bases/moduli) to significantly reduce collision probability.
//   • Pitfalls: Hash collisions: Different strings can produce the same hash, leading to false positives if not handled.; Poor choice of base or modulus can lead to more frequent collisions.
// - Minimum Enclosing Circle (array, geometry, randomized, recursion)
//   • When to use: Use when finding the smallest circle that contains a given set of 2D points. It provides an expected linear time solution for this fundamental geometric problem.
//   • Idea: Welzl's algorithm finds the unique minimum enclosing circle for a set of points using a randomized incremental approach. It achieves an expected time complexity of O(N).
//   • Invariants: The current candidate circle `C` encloses all points `p_1, ..., p_i` processed so far.; If `p_i` is not contained in `C_{i-1}`, then `p_i` must lie on the boundary of `C_i`.
//   • Tips: Randomly permute input points to ensure expected O(N) performance.; The MEC is uniquely determined by either two points forming a diameter or three points on its boundary.
//   • Pitfalls: Not randomizing the input can lead to a worst-case O(N^3) performance.; Floating-point precision issues can cause incorrect boundary checks or point containment tests.
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
int* solveQueries(int* nums, int numsSize, int* queries, int queriesSize, int* returnSize) {
    int* result = (int*)malloc(queriesSize * sizeof(int));
    if (!result) {
        *returnSize = 0;
        return NULL; // Memory allocation failed
    }

    // Create a map to store the last occurrence of each number
    int maxNum = 1000000; // Given constraint: 1 <= nums[i] <= 10^6
    int* lastOccurrence = (int*)malloc((maxNum + 1) * sizeof(int));
    for (int i = 0; i <= maxNum; i++) {
        lastOccurrence[i] = -1; // Initialize all occurrences to -1
    }

    // Create a map to store the minimum distance for each index
    int* minDistance = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        minDistance[i] = -1; // Initialize all distances to -1
    }

    // Calculate minimum distances
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        if (lastOccurrence[num] != -1) {
            int distance = i - lastOccurrence[num];
            if (minDistance[i] == -1 || distance < minDistance[i]) {
                minDistance[i] = distance;
            }
            if (minDistance[lastOccurrence[num]] == -1 || distance < minDistance[lastOccurrence[num]]) {
                minDistance[lastOccurrence[num]] = distance;
            }
        }
        lastOccurrence[num] = i;
    }

    // Handle circular distances
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        if (lastOccurrence[num] != -1 && lastOccurrence[num] != i) {
            int circularDistance = numsSize - (lastOccurrence[num] - i);
            if (minDistance[i] == -1 || circularDistance < minDistance[i]) {
                minDistance[i] = circularDistance;
            }
            if (minDistance[lastOccurrence[num]] == -1 || circularDistance < minDistance[lastOccurrence[num]]) {
                minDistance[lastOccurrence[num]] = circularDistance;
            }
        }
    }

    // Prepare results for queries
    for (int i = 0; i < queriesSize; i++) {
        int queryIndex = queries[i];
        result[i] = minDistance[queryIndex];
    }
    free(lastOccurrence);
    free(minDistance);
    *returnSize = queriesSize;
    return result;     
}
