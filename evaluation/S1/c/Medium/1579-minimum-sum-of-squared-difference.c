// Source: https://leetcode.com/problems/minimum-sum-of-squared-difference/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive 0-indexed integer arrays nums1 and nums2, both of length n.
//
// The sum of squared difference of arrays nums1 and nums2 is defined as the sum of (nums1[i] - nums2[i])2 for each 0 <= i < n.
//
// You are also given two positive integers k1 and k2. You can modify any of the elements of nums1 by +1 or -1 at most k1 times. Similarly, you can modify any of the elements of nums2 by +1 or -1 at most k2 times.
//
// Return the minimum sum of squared difference after modifying array nums1 at most k1 times and modifying array nums2 at most k2 times.
//
// Note: You are allowed to modify the array elements to become negative integers.
//
// Example:
// Input: nums1 = [1,2,3,4], nums2 = [2,10,20,19], k1 = 0, k2 = 0
// Output: 579
// Explanation: The elements in nums1 and nums2 cannot be modified because k1 = 0 and k2 = 0. 
// The sum of square difference will be: (1 - 2)2 + (2 - 10)2 + (3 - 20)2 + (4 - 19)2 = 579.
//
// Constraints:
// n == nums1.length == nums2.length
// 	1 <= n <= 105
// 	0 <= nums1[i], nums2[i] <= 105
// 	0 <= k1, k2 <= 109
//
// Helpful references (internal KB):
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long minSumSquareDiff(int* nums1, int nums1Size, int* nums2, int nums2Size, int k1, int k2) {
    int maxDiff = 0;
    for (int i = 0; i < nums1Size; i++) {
        int diff = nums1[i] > nums2[i] ? nums1[i] - nums2[i] : nums2[i] - nums1[i];
        if (diff > maxDiff) {
            maxDiff = diff;
        }
    }

    long long freq[maxDiff + 1];
    for (int i = 0; i <= maxDiff; i++) {
        freq[i] = 0;
    }

    for (int i = 0; i < nums1Size; i++) {
        int diff = nums1[i] > nums2[i] ? nums1[i] - nums2[i] : nums2[i] - nums1[i];
        freq[diff]++;
    }

    long long k = (long long)k1 + (long long)k2;
    for (int d = maxDiff; d > 0 && k > 0; d--) {
        if (freq[d] == 0) {
            continue;
        }

        long long totalReduce = freq[d] < k ? freq[d] : k;
        freq[d] -= totalReduce;
        freq[d - 1] += totalReduce;
        k -= totalReduce;

        if (freq[d] > 0) {
            long long fullRows = k / freq[d];
            if (fullRows > 0) {
                long long reduceRows = fullRows < d ? fullRows : d;
                freq[d - reduceRows] += freq[d];
                freq[d] = 0;
                k -= reduceRows * freq[d];
            }

            if (freq[d] > 0 && k > 0) {
                freq[d - 1] += k;
                freq[d] -= k;
                k = 0;
            }
        }
    }

    long long result = 0;
    for (int d = 1; d <= maxDiff; d++) {
        if (freq[d] > 0) {
            result += (long long)freq[d] * (long long)d * (long long)d;
        }
    }

    return result;      
}
