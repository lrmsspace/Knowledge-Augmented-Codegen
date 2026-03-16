// Source: https://leetcode.com/problems/count-partitions-with-even-sum-difference/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums of length n.
//
// A partition is defined as an index i where 0 <= i < n - 1, splitting the array into two non-empty subarrays such that:
//
//
// 	Left subarray contains indices [0, i].
// 	Right subarray contains indices [i + 1, n - 1].
//
//
// Return the number of partitions where the difference between the sum of the left and right subarrays is even.
//
// Example:
// Input: nums = [10,10,3,7,6]
//
// Output: 4
//
// Explanation:
//
// The 4 partitions are:
//
//
// 	[10], [10, 3, 7, 6] with a sum difference of 10 - 26 = -16, which is even.
// 	[10, 10], [3, 7, 6] with a sum difference of 20 - 16 = 4, which is even.
// 	[10, 10, 3], [7, 6] with a sum difference of 23 - 13 = 10, which is even.
// 	[10, 10, 3, 7], [6] with a sum difference of 30 - 6 = 24, which is even.
//
// Constraints:
// 2 <= n == nums.length <= 100
// 	1 <= nums[i] <= 100
//
// Helpful references (internal KB):
// - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
//   • When to use: When you need to calculate the area of a simple polygon given its vertices in sequential order. It efficiently handles both convex and non-convex polygons.
//   • Idea: This algorithm calculates the area of a simple polygon by summing the signed areas of trapezoids or triangles formed by its edges and a reference point/axis. It achieves O(N) time complexity.
//   • Invariants: The sum accumulates the signed area contribution of processed edges.; The current vertex and the next vertex define an edge of the polygon.
//   • Tips: Ensure vertices are provided in sequential order (clockwise or counter-clockwise).; The absolute value of the final result is the polygon's area.
//   • Pitfalls: Supplying vertices in a non-sequential or arbitrary order will yield an incorrect area.; Applying the formula to self-intersecting polygons will not give the true geometric area.
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
// - Sqrt Decomposition (array, enumeration, prefix-sum)
//   • When to use: Use when frequent range queries and point/range updates are needed on an array, offering a balanced O(sqrt(N)) time complexity for both operations. It's a good alternative when a segment tree is too complex or overkill.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and updates. It achieves an O(sqrt(N)) time complexity for both query and update operations.
//   • Invariants: Each block maintains an up-to-date aggregate of its elements.; For any query, fully contained blocks are processed using their precomputed aggregates.
//   • Tips: Choose block size carefully, typically sqrt(N) for optimal balance.; Precompute block aggregates (sum, min, max) for efficient queries.
//   • Pitfalls: Incorrectly handling partial blocks or boundary conditions.; Off-by-one errors in block indices or element indices within blocks.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countPartitions(int* nums, int numsSize) {
    int evenCount = 0, oddCount = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] % 2 == 0) {
            evenCount++;
        } else {
            oddCount++;
        }
    }

    // The difference between the sums of the two subarrays is even if both subarrays have an even count of odd numbers or both have an odd count of odd numbers.
    // This can be calculated using combinations of even and odd counts.
    int totalPartitions = (evenCount * (evenCount - 1)) / 2 + (oddCount * (oddCount - 1)) / 2;
    
    return totalPartitions;     
}
