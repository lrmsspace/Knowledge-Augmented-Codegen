// Source: https://leetcode.com/problems/find-score-of-an-array-after-marking-all-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums consisting of positive integers.
//
// Starting with score = 0, apply the following algorithm:
//
//
// 	Choose the smallest integer of the array that is not marked. If there is a tie, choose the one with the smallest index.
// 	Add the value of the chosen integer to score.
// 	Mark the chosen element and its two adjacent elements if they exist.
// 	Repeat until all the array elements are marked.
//
//
// Return the score you get after applying the above algorithm.
//
// Example:
// Input: nums = [2,1,3,4,5,2]
// Output: 7
// Explanation: We mark the elements as follows:
// - 1 is the smallest unmarked element, so we mark it and its two adjacent elements: [2,1,3,4,5,2].
// - 2 is the smallest unmarked element, so we mark it and its left adjacent element: [2,1,3,4,5,2].
// - 4 is the only remaining unmarked element, so we mark it: [2,1,3,4,5,2].
// Our score is 1 + 2 + 4 = 7.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 106
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - MEX (minimal excluded) of a sequence (ds, enumeration)
//   • When to use: Use when needing to efficiently find the smallest non-negative integer not present in a dynamic sequence or range, supporting both updates and queries in logarithmic time.
//   • Idea: This technique finds the Minimal Excluded (MEX) value in a sequence by maintaining counts of distinct elements in ranges using a specialized data structure, typically a segment tree. It supports both updates and queries in O(log N) time.
//   • Invariants: Each segment tree node accurately reflects the count of distinct numbers within its corresponding range.; If a range [L, R) contains R-L distinct numbers, then all integers from L to R-1 are present.
//   • Tips: Implement a segment tree where each node stores the count of distinct numbers in its range.; The binary search for MEX checks if a range [0, k) contains k distinct numbers to decide which child to traverse.
//   • Pitfalls: Incorrectly calculating distinct counts in segment tree nodes, especially after updates.; Off-by-one errors when comparing the number of distinct elements with the expected count for a full range.
// - Elementary Sorts (array, enumeration)
//   • When to use: Selection sort is simple but inefficient. It's suitable for very small datasets or educational purposes where simplicity of implementation is prioritized over performance.
//   • Idea: Selection sort repeatedly finds the minimum element from the unsorted portion of the array and places it at the beginning of the sorted portion. It has a time complexity of O(N^2) and a space complexity of O(1).
//   • Invariants: The elements in the prefix of the array are sorted.; All elements in the sorted prefix are less than or equal to all elements in the unsorted suffix.
//   • Tips: Easy to understand and implement.; Performs a minimal number of swaps (exactly N-1 swaps).
//   • Pitfalls: Inefficient for large datasets due to O(N^2) time complexity.; Performance is not affected by the initial order of elements.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long findScore(int* nums, int numsSize) {
    long long score = 0;
    int* marked = (int*)calloc(numsSize, sizeof(int)); // Array to keep track of marked elements

    for (int i = 0; i < numsSize; i++) {
        if (marked[i]) {
            continue; // Skip if already marked
        }

        // Find the smallest unmarked element
        int minIndex = i;
        for (int j = i + 1; j < numsSize; j++) {
            if (!marked[j] && nums[j] < nums[minIndex]) {
                minIndex = j;
            }
        }

        // Add the value of the chosen integer to score
        score += nums[minIndex];

        // Mark the chosen element and its two adjacent elements
        marked[minIndex] = 1; // Mark the chosen element
        if (minIndex - 1 >= 0) {
            marked[minIndex - 1] = 1; // Mark left adjacent element if it exists
        }
        if (minIndex + 1 < numsSize) {
            marked[minIndex + 1] = 1; // Mark right adjacent element if it exists
        }
    }

    free(marked); // Free the allocated memory for marked array
    return score;       
}
