// Source: https://leetcode.com/problems/maximize-subarray-gcd-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of positive integers nums and an integer k.
//
// You may perform at most k operations. In each operation, you can choose one element in the array and double its value. Each element can be doubled at most once.
//
// The score of a contiguous subarray is defined as the product of its length and the greatest common divisor (GCD) of all its elements.
//
// Your task is to return the maximum score that can be achieved by selecting a contiguous subarray from the modified array.
//
// Note:
//
//
//  The greatest common divisor (GCD) of an array is the largest integer that evenly divides all the array elements.
//
// Example:
// Input: nums = [2,4], k = 1
//
// Output: 8
//
// Explanation:
//
//
//  Double nums[0] to 4 using one operation. The modified array becomes [4, 4].
//  The GCD of the subarray [4, 4] is 4, and the length is 2.
//  Thus, the maximum possible score is 2 × 4 = 8.
//
// Constraints:
// 1 <= n == nums.length <= 1500
//  1 <= nums[i] <= 109
//  1 <= k <= n
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp)
//   • When to use: When a problem involves finding an optimal value for a contiguous range of elements, and solutions for larger ranges can be derived by merging optimal solutions of smaller sub-ranges.
//   • Idea: An extension of dynamic programming where subproblems are defined over contiguous intervals, solving for dp[i][j] by iterating through all possible split points k within [i, j]. This often results in O(N^3) time complexity.
//   • Invariants: dp[i][j] represents the optimal solution for the interval [i, j].; When computing dp[i][j], all subproblems dp[x][y] where y - x + 1 < j - i + 1 are already solved.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length, then by start index.
//   • Pitfalls: Off-by-one errors in interval boundaries or split points.; Incorrect iteration order, leading to uncomputed subproblems.
// - Euclidean algorithm for computing the greatest common divisor (number, gcd)
//   • When to use: Use this algorithm to efficiently find the greatest common divisor of two or more integers, or as a subroutine for tasks like simplifying fractions or finding the least common multiple.
//   • Idea: The Euclidean algorithm is an efficient method for computing the greatest common divisor (GCD) of two non-negative integers by repeatedly applying the division algorithm. It operates in logarithmic time complexity, O(log min(a, b)).
//   • Invariants: The greatest common divisor of the current pair (a, b) remains constant and equal to the GCD of the original inputs.; The second number (b) is always non-negative.
//   • Tips: Handle the base case where one of the numbers is zero; gcd(a, 0) = a.; The algorithm works for any order of inputs; if a < b, the first step swaps them effectively.
//   • Pitfalls: Forgetting to take absolute values if negative inputs are possible, as GCD is typically defined for non-negative integers.; Incorrectly handling the zero input case, which can lead to infinite loops or incorrect results.
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long maxGCDScore(int[] nums, int k) {
        int n = nums.length;
        long maxScore = 0;

        for (int start = 0; start < n; start++) {
            for (int end = start; end < n; end++) {
                int length = end - start + 1;
                int gcd = 0;
                for (int i = start; i <= end; i++) {
                    gcd = gcd(gcd, nums[i]);
                }

                int neededDoubles = 0;
                for (int i = start; i <= end; i++) {
                    if ((nums[i] / gcd) % 2 != 0) {
                        neededDoubles++;
                    }
                }

                if (neededDoubles <= k) {
                    long score = (long) length * gcd;
                    maxScore = Math.max(maxScore, score);
                }
            }
        }

        return maxScore;            
    }
}
