// Source: https://leetcode.com/problems/burst-balloons/   |   Difficulty: Hard
//
// Problem Description:
// You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it represented by an array nums. You are asked to burst all the balloons.
//
// If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins. If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a balloon with a 1 painted on it.
//
// Return the maximum coins you can collect by bursting the balloons wisely.
//
// Example:
// Input: nums = [3,1,5,8]
// Output: 167
// Explanation:
// nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
// coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
//
// Constraints:
// n == nums.length
// 	1 <= n <= 300
// 	0 <= nums[i] <= 100
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
// - Continued fractions (number, array, enumeration)
//   • When to use: Use when representing real numbers as a sequence of integers for rational approximation, or when analyzing properties of irrational numbers. It's also useful for solving certain Diophantine equations and Pell's equation.
//   • Idea: Continued fractions represent a real number as a sum of an integer and the reciprocal of another number, which is then represented in the same way. This process generates a sequence of integers, and its complexity depends on the desired precision or the number's nature.
//   • Invariants: The current integer term `a_i` is `floor(x_i)`, where `x_i` is the current real value being expanded.; The next real value `x_{i+1}` is `1 / (x_i - a_i)` if `x_i - a_i` is non-zero.
//   • Tips: Understand the recursive definition of continued fractions.; The Euclidean algorithm forms the basis for computing finite continued fractions.
//   • Pitfalls: Floating-point precision issues can severely limit accuracy for irrational numbers.; Misinterpreting convergents as exact values instead of approximations.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maxCoins(int[] nums) {
        int n = nums.length;
        int[] balloons = new int[n + 2];
        balloons[0] = 1;
        balloons[n + 1] = 1;
        System.arraycopy(nums, 0, balloons, 1, n);

        int[][] dp = new int[n + 2][n + 2];

        for (int length = 1; length <= n; length++) {
            for (int left = 1; left <= n - length + 1; left++) {
                int right = left + length - 1;
                for (int i = left; i <= right; i++) {
                    dp[left][right] = Math.max(dp[left][right],
                            dp[left][i - 1] + balloons[left - 1] * balloons[i] * balloons[right + 1] + dp[i + 1][right]);
                }
            }
        }

        return dp[1][n];            
    }
}
