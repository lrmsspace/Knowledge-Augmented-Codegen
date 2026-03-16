// Source: https://leetcode.com/problems/sum-of-squares-of-special-elements/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 1-indexed integer array nums of length n.
//
// An element nums[i] of nums is called special if i divides n, i.e. n % i == 0.
//
// Return the sum of the squares of all special elements of nums.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: 21
// Explanation: There are exactly 3 special elements in nums: nums[1] since 1 divides 4, nums[2] since 2 divides 4, and nums[4] since 4 divides 4. 
// Hence, the sum of the squares of all special elements of nums is nums[1] * nums[1] + nums[2] * nums[2] + nums[4] * nums[4] = 1 * 1 + 2 * 2 + 4 * 4 = 21.
//
// Constraints:
// 1 <= nums.length == n <= 50
// 	1 <= nums[i] <= 50
//
// Helpful references (internal KB):
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
// - Integration by Simpson's formula (number, interval, enumeration, simulation)
//   • When to use: Use when approximating definite integrals of functions that are sufficiently smooth over a given interval. It is effective for achieving good accuracy with a moderate number of subintervals.
//   • Idea: Simpson's formula approximates a definite integral by dividing the integration interval into an even number of subintervals and approximating the function over each pair of subintervals with a parabola. This method offers a higher order of accuracy compared to simpler rules, typically achieving O(N^4) accuracy for N subintervals.
//   • Invariants: The sum accumulates weighted function values for all processed subintervals.; The subinterval width 'h' remains constant across the entire integration range.
//   • Tips: Ensure the total number of subintervals (2n) is always even for the composite rule.; The weights for function evaluations follow a specific 1-4-2-4-...-2-4-1 pattern.
//   • Pitfalls: Incorrectly applying the weighting coefficients, especially at the boundaries or interior points.; Using an odd number of subintervals, which invalidates the parabolic approximation for the composite rule.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int sumOfSquares(int* nums, int numsSize) {
    int sum = 0;
    for (int i = 1; i <= numsSize; i++) {
        if (numsSize % i == 0) {
            sum += nums[i - 1] * nums[i - 1];
        }
    }
    return sum;     
}
