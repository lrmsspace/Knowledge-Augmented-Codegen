// Source: https://leetcode.com/problems/minimum-absolute-sum-difference/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integer arrays nums1 and nums2, both of length n.
//
// The absolute sum difference of arrays nums1 and nums2 is defined as the sum of |nums1[i] - nums2[i]| for each 0 <= i < n (0-indexed).
//
// You can replace at most one element of nums1 with any other element in nums1 to minimize the absolute sum difference.
//
// Return the minimum absolute sum difference after replacing at most one element in the array nums1. Since the answer may be large, return it modulo 109 + 7.
//
// |x| is defined as:
//
//
// 	x if x >= 0, or
// 	-x if x < 0.
//
// Example:
// Input: nums1 = [1,7,5], nums2 = [2,3,5]
// Output: 3
// Explanation: There are two possible optimal solutions:
// - Replace the second element with the first: [1,7,5] => [1,1,5], or
// - Replace the second element with the third: [1,7,5] => [1,5,5].
// Both will yield an absolute sum difference of |1-2| + (|1-3| or |5-3|) + |5-5| = 3.
//
// Constraints:
// n == nums1.length
// 	n == nums2.length
// 	1 <= n <= 105
// 	1 <= nums1[i], nums2[i] <= 105
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
// - Ternary Search (interval, number, binary-search, enumeration)
//   • When to use: Use Ternary Search to find the minimum or maximum of a unimodal or bitonic function over a continuous or discrete interval. It is effective when the function's derivative is hard to compute or unavailable.
//   • Idea: Ternary search is a divide and conquer algorithm that repeatedly narrows down the search space for the extremum of a unimodal function by evaluating two points within the current interval. It reduces the search interval by one-third in each step, achieving O(log N) time complexity.
//   • Invariants: The extremum of the unimodal function lies within the current interval [l, r].; The function value at m1 is compared with m2 to narrow the search.
//   • Tips: Ensure the function is strictly unimodal or bitonic within the search range.; Handle floating-point precision carefully for continuous functions.
//   • Pitfalls: Applying to non-unimodal functions yields incorrect results.; Floating-point errors can lead to incorrect bounds or infinite loops.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minAbsoluteSumDiff(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    #define MOD 1000000007
    #define MAX_VAL 100000

    int sortedNums1[MAX_VAL + 1] = {0};
    for (int i = 0; i < nums1Size; i++) {
        sortedNums1[nums1[i]] = 1;
    }
    for (int i = 1; i <= MAX_VAL; i++) {
        sortedNums1[i] += sortedNums1[i - 1];
    }

    long long totalDiff = 0;
    int maxImprovement = 0;

    for (int i = 0; i < nums1Size; i++) {
        int diff = nums1[i] > nums2[i] ? nums1[i] - nums2[i] : nums2[i] - nums1[i];
        totalDiff = (totalDiff + diff) % MOD;

        int target = nums2[i];
        int left = 0, right = MAX_VAL, bestCandidate = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (sortedNums1[mid] > sortedNums1[target]) {
                bestCandidate = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        if (bestCandidate != -1) {
            int newDiff = bestCandidate > target ? bestCandidate - target : target - bestCandidate;
            int improvement = diff - newDiff;
            if (improvement > maxImprovement) {
                maxImprovement = improvement;
            }
        }

        if (target > 0) {
            left = 0;
            right = MAX_VAL;
            bestCandidate = -1;

            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (sortedNums1[mid] >= sortedNums1[target - 1]) {
                    bestCandidate = mid;
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }

            if (bestCandidate != -1) {
                int newDiff = bestCandidate > target ? bestCandidate - target : target - bestCandidate;
                int improvement = diff - newDiff;
                if (improvement > maxImprovement) {
                    maxImprovement = improvement;
                }
            }
        }
    }
    return (totalDiff - maxImprovement + MOD) % MOD;
}
