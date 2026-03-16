// Source: https://leetcode.com/problems/number-of-pairs-satisfying-inequality/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed integer arrays nums1 and nums2, each of size n, and an integer diff. Find the number of pairs (i, j) such that:
//
//
// 	0 <= i < j <= n - 1 and
// 	nums1[i] - nums1[j] <= nums2[i] - nums2[j] + diff.
//
//
// Return the number of pairs that satisfy the conditions.
//
// Example:
// Input: nums1 = [3,2,5], nums2 = [2,2,1], diff = 1
// Output: 3
// Explanation:
// There are 3 pairs that satisfy the conditions:
// 1. i = 0, j = 1: 3 - 2 <= 2 - 2 + 1. Since i < j and 1 <= 1, this pair satisfies the conditions.
// 2. i = 0, j = 2: 3 - 5 <= 2 - 1 + 1. Since i < j and -2 <= 2, this pair satisfies the conditions.
// 3. i = 1, j = 2: 2 - 5 <= 2 - 1 + 1. Since i < j and -3 <= 2, this pair satisfies the conditions.
// Therefore, we return 3.
//
// Constraints:
// n == nums1.length == nums2.length
// 	2 <= n <= 105
// 	-104 <= nums1[i], nums2[i] <= 104
// 	-104 <= diff <= 104
//
// Helpful references (internal KB):
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when an array requires frequent point updates and efficient retrieval of prefix sums or range sums. It offers logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently supports point updates and prefix sum queries on an array in O(log N) time.
//   • Invariants: Each `bit[i]` stores the sum of a contiguous range of elements from the original array.; The range length represented by `bit[i]` is determined by `i & -i` (the least significant bit).
//   • Tips: Use 1-based indexing for simpler bitwise operations (`i & -i`).; Initialize with an existing array in O(N) time using a linear construction method.
//   • Pitfalls: Directly finding range minimum/maximum is not efficient or generally supported.; Operations must be associative and preferably invertible for general range queries.
// - The Inclusion-Exclusion Principle (array, number, counting, sieve)
//   • When to use: Use when direct counting of elements satisfying specific conditions is difficult due to overlaps, and you need to find the count of elements satisfying at least one, exactly k, or none of several properties.
//   • Idea: The Inclusion-Exclusion Principle counts the size of a union of sets by alternately adding and subtracting the sizes of intersections of increasing numbers of sets. Its complexity is often exponential in the number of properties.
//   • Invariants: At the start of processing subsets of size k, the running total correctly accounts for all intersections of size less than k.; For every element x, its contribution to the total sum is 1 if it satisfies the target condition, and 0 otherwise.
//   • Tips: Clearly define the properties (P1, P2, ..., Pn) for which elements are counted.; Systematically calculate the sizes of all relevant intersections of properties.
//   • Pitfalls: Incorrectly defining the properties or the universe of elements being counted.; Errors in calculating the sizes of specific intersections of properties.
// - Linear Diophantine Equation (number, interval, enumeration)
//   • When to use: Use when you need to find or count all integer solutions (x, y) for a linear Diophantine equation ax + by = c, especially when solutions are constrained within specific intervals for x and y.
//   • Idea: This method finds all integer solutions to a linear Diophantine equation ax + by = c within given x and y intervals. It first finds a particular solution, then uses properties of the general solution to determine the valid range for x, and enumerates solutions in O(N) time where N is the number of solutions.
//   • Invariants: The current (x, y) pair always satisfies the linear Diophantine equation ax + by = c.; The current x value is an integer and satisfies the effective bounds l_x <= x <= r_x.
//   • Tips: Pre-divide coefficients a, b, c by gcd(a, b) to simplify the equation.; Use the Extended Euclidean Algorithm to find an initial particular solution (x0, y0).
//   • Pitfalls: Failing to check if c is divisible by gcd(a, b) before proceeding, leading to incorrect results.; Incorrectly applying the shifting logic for x and y bounds, resulting in an invalid solution range.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long numberOfPairs(int* nums1, int nums1Size, int* nums2, int nums2Size, int diff) {
    int n = nums1Size;
    int *arr = (int*)malloc(n * sizeof(int));
    if (!arr) return 0;
    for (int i = 0; i < n; ++i) {
        arr[i] = nums1[i] - nums2[i];
    }

    /* Coordinate compression */
    int *sorted = (int*)malloc(n * sizeof(int));
    if (!sorted) { free(arr); return 0; }
    memcpy(sorted, arr, n * sizeof(int));
    qsort(sorted, n, sizeof(int), cmpInt);
    int uniqueCount = 0;
    for (int i = 0; i < n; ++i) {
        if (i == 0 || sorted[i] != sorted[i - 1]) {
            sorted[uniqueCount++] = sorted[i];
        }
    }

    /* Fenwick Tree */
    int *bit = (int*)calloc(uniqueCount + 1, sizeof(int));
    if (!bit) { free(arr); free(sorted); return 0; }

    long long result = 0;
    for (int i = 0; i < n; ++i) {
        int target = arr[i] + diff;
        int idx = upperBound(sorted, uniqueCount, target);
        result += queryBIT(bit, idx);

        int arrIdx = lowerBound(sorted, uniqueCount, arr[i]);
        updateBIT(bit, uniqueCount, arrIdx + 1, 1);
    }
    free(arr);
    free(sorted);
    free(bit);
    return result;
}
