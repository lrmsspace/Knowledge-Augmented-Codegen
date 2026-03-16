// Source: https://leetcode.com/problems/get-the-maximum-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given two sorted arrays of distinct integers nums1 and nums2.
//
// A valid path is defined as follows:
//
//
// 	Choose array nums1 or nums2 to traverse (from index-0).
// 	Traverse the current array from left to right.
// 	If you are reading any value that is present in nums1 and nums2 you are allowed to change your path to the other array. (Only one repeated value is considered in the valid path).
//
//
// The score is defined as the sum of unique values in a valid path.
//
// Return the maximum score you can obtain of all possible valid paths. Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: nums1 = [2,4,5,8,10], nums2 = [4,6,8,9]
// Output: 30
// Explanation: Valid paths:
// [2,4,5,8,10], [2,4,5,8,9], [2,4,6,8,9], [2,4,6,8,10],  (starting from nums1)
// [4,6,8,9], [4,5,8,10], [4,5,8,9], [4,6,8,10]    (starting from nums2)
// The maximum is obtained with the path in green [2,4,6,8,10].
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 105
// 	1 <= nums1[i], nums2[i] <= 107
// 	nums1 and nums2 are strictly increasing.
//
// Helpful references (internal KB):
// - Minkowski sum of convex polygons (geometry, array, two-pointers, sweep-line)
//   • When to use: Use this algorithm to compute the Minkowski sum of two convex polygons efficiently. It is ideal for applications requiring the union of shapes or collision detection between convex objects.
//   • Idea: This algorithm computes the Minkowski sum of two convex polygons by merging their edge vectors, sorted by polar angle, into a new sequence of edges. The resulting sum polygon is also convex and can be constructed in O(|P| + |Q|) time.
//   • Invariants: The current vertex of the resulting sum polygon is the sum of the current vertices from P and Q.; All edges processed so far from both input polygons have been added to the output in polar angle order.
//   • Tips: Pre-sort polygon vertices to start from the lowest Y-coordinate to ensure consistent orientation.; Orient both input polygons counter-clockwise for correct edge vector generation.
//   • Pitfalls: Incorrectly handling polygon orientation (e.g., mixing clockwise and counter-clockwise).; Precision issues when using floating-point numbers for angle comparisons or vector additions.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Discrete Logarithm (array, number, binary-search, mod-exp)
//   • When to use: Use when solving for the exponent 'x' in the modular equation a^x = b (mod m), especially when 'm' is large and a and m are coprime. It's suitable for finding a solution within O(sqrt(m) log m) time.
//   • Idea: This algorithm, also known as Baby-step Giant-step, finds the smallest non-negative integer 'x' satisfying a^x = b (mod m) using a meet-in-the-middle approach. It achieves a time complexity of O(sqrt(m) log m).
//   • Invariants: The map stores (a^q mod m, q) for all baby steps q in [0, n-1].; For each giant step p, a^(np) mod m is correctly computed.
//   • Tips: Choose 'n' as ceil(sqrt(m)) for balanced steps.; Use a hash map to store baby steps for O(1) average lookup.
//   • Pitfalls: Incorrect choice of 'n' can lead to suboptimal time complexity.; Failure to check if 'a' and 'm' are coprime may yield no solution or incorrect results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxSum(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    const int MOD = 1000000007;
    long long sum1 = 0, sum2 = 0;
    int i = 0, j = 0;

    while (i < nums1Size || j < nums2Size) {
        if (i < nums1Size && (j == nums2Size || nums1[i] < nums2[j])) {
            sum1 += nums1[i++];
        } else if (j < nums2Size && (i == nums1Size || nums1[i] > nums2[j])) {
            sum2 += nums2[j++];
        } else {
            long long maxSum = (sum1 > sum2 ? sum1 : sum2) + nums1[i];
            sum1 = maxSum;
            sum2 = maxSum;
            i++;
            j++;
        }
    }

    long long result = (sum1 > sum2 ? sum1 : sum2) % MOD;
    return (int)result;     
}
