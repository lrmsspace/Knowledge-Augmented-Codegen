// Source: https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/   |   Difficulty: Easy
//
// Problem Description:
// Given an array nums, return true if the array was originally sorted in non-decreasing order, then rotated some number of positions (including zero). Otherwise, return false.
//
// There may be duplicates in the original array.
//
// Note: An array A rotated by x positions results in an array B of the same length such that B[i] == A[(i+x) % A.length] for every valid index i.
//
// Example:
// Input: nums = [3,4,5,1,2]
// Output: true
// Explanation: [1,2,3,4,5] is the original sorted array.
// You can rotate the array by x = 2 positions to begin on the element of value 3: [3,4,5,1,2].
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 100
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Elementary Sorts (array, enumeration)
//   • When to use: Selection sort is simple but inefficient. It's suitable for very small datasets or educational purposes where simplicity of implementation is prioritized over performance.
//   • Idea: Selection sort repeatedly finds the minimum element from the unsorted portion of the array and places it at the beginning of the sorted portion. It has a time complexity of O(N^2) and a space complexity of O(1).
//   • Invariants: The elements in the prefix of the array are sorted.; All elements in the sorted prefix are less than or equal to all elements in the unsorted suffix.
//   • Tips: Easy to understand and implement.; Performs a minimal number of swaps (exactly N-1 swaps).
//   • Pitfalls: Inefficient for large datasets due to O(N^2) time complexity.; Performance is not affected by the initial order of elements.
// - Burnside's lemma / Pólya enumeration theorem (array, number, enumeration, simulation)
//   • When to use: Use when counting the number of distinct configurations or arrangements of objects under a set of symmetry operations, where configurations are considered identical if one can be transformed into another by a group action.
//   • Idea: Burnside's Lemma and Pólya Enumeration Theorem are combinatorial tools used to count the number of distinct objects under a group of symmetries. Both typically involve iterating through group elements and analyzing permutation cycle structures, often resulting in polynomial time complexity depending on group size and element analysis.
//   • Invariants: The set of group elements considered remains consistent throughout the summation.; Each group element's cycle decomposition is correctly identified.
//   • Tips: Identify the group of symmetry operations acting on the objects.; For each group element, determine its permutation cycle structure.
//   • Pitfalls: Incorrectly identifying the full set of distinct group operations.; Errors in determining the cycle structure of permutations.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool check(int* nums, int numsSize) {
    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > nums[(i + 1) % numsSize]) {
            count++;
            if (count > 1) {
                return false;
            }
        }
    }
    return true;        
}
