// Source: https://leetcode.com/problems/find-the-difference-of-two-arrays/   |   Difficulty: Easy
//
// Problem Description:
// Given two 0-indexed integer arrays nums1 and nums2, return a list answer of size 2 where:
//
//
// 	answer[0] is a list of all distinct integers in nums1 which are not present in nums2.
// 	answer[1] is a list of all distinct integers in nums2 which are not present in nums1.
//
//
// Note that the integers in the lists may be returned in any order.
//
// Example:
// Input: nums1 = [1,2,3], nums2 = [2,4,6]
// Output: [[1,3],[4,6]]
// Explanation:
// For nums1, nums1[1] = 2 is present at index 0 of nums2, whereas nums1[0] = 1 and nums1[2] = 3 are not present in nums2. Therefore, answer[0] = [1,3].
// For nums2, nums2[0] = 2 is present at index 1 of nums1, whereas nums2[1] = 4 and nums2[2] = 6 are not present in nums1. Therefore, answer[1] = [4,6].
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 1000
// 	-1000 <= nums1[i], nums2[i] <= 1000
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (array, number, counting, sieve)
//   • When to use: Use when direct counting of elements satisfying specific conditions is difficult due to overlaps, and you need to find the count of elements satisfying at least one, exactly k, or none of several properties.
//   • Idea: The Inclusion-Exclusion Principle counts the size of a union of sets by alternately adding and subtracting the sizes of intersections of increasing numbers of sets. Its complexity is often exponential in the number of properties.
//   • Invariants: At the start of processing subsets of size k, the running total correctly accounts for all intersections of size less than k.; For every element x, its contribution to the total sum is 1 if it satisfies the target condition, and 0 otherwise.
//   • Tips: Clearly define the properties (P1, P2, ..., Pn) for which elements are counted.; Systematically calculate the sizes of all relevant intersections of properties.
//   • Pitfalls: Incorrectly defining the properties or the universe of elements being counted.; Errors in calculating the sizes of specific intersections of properties.
// - String Hashing (string, number, hashing)
//   • When to use: Use when needing to compare strings or substrings quickly, reducing comparison time from linear to constant. It is ideal for problems requiring frequent string equality checks or pattern matching across large texts.
//   • Idea: String hashing maps a string to an integer hash value, allowing for O(1) equality checks between strings or substrings. This technique relies on a hash function where equal strings must produce equal hashes, though the reverse is not guaranteed.
//   • Invariants: The hash of any prefix s[0...i] is correctly computed based on s[0...i-1] and s[i].; All characters processed up to the current index i contribute to the current hash value.
//   • Tips: Use a polynomial rolling hash function with a prime base and a large prime modulus.; Employ double hashing (two different bases/moduli) to significantly reduce collision probability.
//   • Pitfalls: Hash collisions: Different strings can produce the same hash, leading to false positives if not handled.; Poor choice of base or modulus can lead to more frequent collisions.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findDifference(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize, int** returnColumnSizes) {
    int hash1[2001] = {0};
    int hash2[2001] = {0};
    for (int i = 0; i < nums1Size; i++) {
        hash1[nums1[i] + 1000] = 1;
    }
    for (int i = 0; i < nums2Size; i++) {
        hash2[nums2[i] + 1000] = 1;
    }

    int **result = (int **)malloc(2 * sizeof(int *));
    *returnColumnSizes = (int *)malloc(2 * sizeof(int));
    (*returnColumnSizes)[0] = 0;
    (*returnColumnSizes)[1] = 0;

    // Find elements in nums1 not in nums2
    for (int i = 0; i < 2001; i++) {
        if (hash1[i] == 1 && hash2[i] == 0) {
            (*returnColumnSizes)[0]++;
        }
    }
    result[0] = (int *)malloc((*returnColumnSizes)[0] * sizeof(int));
    int index1 = 0;
    for (int i = 0; i < 2001; i++) {
        if (hash1[i] == 1 && hash2[i] == 0) {
            result[0][index1++] = i - 1000;
        }
    }

    // Find elements in nums2 not in nums1
    for (int i = 0; i < 2001; i++) {
        if (hash2[i] == 1 && hash1[i] == 0) {
            (*returnColumnSizes)[1]++;
        }
    }
    result[1] = (int *)malloc((*returnColumnSizes)[1] * sizeof(int));
    int index2 = 0;
    for (int i = 0; i < 2001; i++) {
        if (hash2[i] == 1 && hash1[i] == 0) {
            result[1][index2++] = i - 1000;
        }
    }

    *returnSize = 2;
    return result;      
}
