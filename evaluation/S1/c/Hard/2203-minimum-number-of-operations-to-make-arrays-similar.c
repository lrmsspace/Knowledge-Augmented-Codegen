// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-arrays-similar/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integer arrays nums and target, of the same length.
//
// In one operation, you can choose any two distinct indices i and j where 0 <= i, j < nums.length and:
//
//
// 	set nums[i] = nums[i] + 2 and
// 	set nums[j] = nums[j] - 2.
//
//
// Two arrays are considered to be similar if the frequency of each element is the same.
//
// Return the minimum number of operations required to make nums similar to target. The test cases are generated such that nums can always be similar to target.
//
// Example:
// Input: nums = [8,12,6], target = [2,14,10]
// Output: 2
// Explanation: It is possible to make nums similar to target in two operations:
// - Choose i = 0 and j = 2, nums = [10,12,4].
// - Choose i = 1 and j = 2, nums = [10,14,2].
// It can be shown that 2 is the minimum number of operations needed.
//
// Constraints:
// n == nums.length == target.length
// 	1 <= n <= 105
// 	1 <= nums[i], target[i] <= 106
// 	It is possible to make nums similar to target.
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, especially for large datasets or external sorting where data might not fit in memory.
//   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and requires O(N) auxiliary space.
//   • Invariants: The elements `index[lo...k-1]` are sorted and contain the smallest `k-lo` elements from the original `aux[lo...mid]` and `aux[mid+1...hi]` segments.; Pointer `i` always indicates the next element to consider from the left sorted sub-array (`aux[lo...mid]`).
//   • Tips: Implement the merge step carefully to ensure stability.; Consider an iterative bottom-up approach to avoid recursion overhead.
//   • Pitfalls: High auxiliary space complexity (O(N)) can be a concern for memory-constrained systems.; Recursive calls can lead to stack overflow for very large inputs without tail call optimization.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
//   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
//   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
//   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
//   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
//   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long makeSimilar(int* nums, int numsSize, int* target, int targetSize) {
    /* Separate even and odd numbers */
    int *numsEven = (int*)malloc(numsSize * sizeof(int));
    int *numsOdd = (int*)malloc(numsSize * sizeof(int));
    int *targetEven = (int*)malloc(targetSize * sizeof(int));
    int *targetOdd = (int*)malloc(targetSize * sizeof(int));
    int numsEvenSize = 0, numsOddSize = 0;
    int targetEvenSize = 0, targetOddSize = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] % 2 == 0) {
            numsEven[numsEvenSize++] = nums[i];
        } else {
            numsOdd[numsOddSize++] = nums[i];
        }
    }

    for (int i = 0; i < targetSize; i++) {
        if (target[i] % 2 == 0) {
            targetEven[targetEvenSize++] = target[i];
        } else {
            targetOdd[targetOddSize++] = target[i];
        }
    }

    /* Sort the separated arrays */
    qsort(numsEven, numsEvenSize, sizeof(int), cmpInt);
    qsort(numsOdd, numsOddSize, sizeof(int), cmpInt);
    qsort(targetEven, targetEvenSize, sizeof(int), cmpInt);
    qsort(targetOdd, targetOddSize, sizeof(int), cmpInt);

    /* Calculate the number of operations needed */
    long long operations = 0;
    for (int i = 0; i < numsEvenSize; i++) {
        operations += llabs(numsEven[i] - targetEven[i]) / 2;
    }
    for (int i = 0; i < numsOddSize; i++) {
        operations += llabs(numsOdd[i] - targetOdd[i]) / 2;
    }

    free(numsEven);
    free(numsOdd);
    free(targetEven);
    free(targetOdd);

    /* Each operation adjusts two elements, so divide by 2 */
    return operations / 2;      
}
