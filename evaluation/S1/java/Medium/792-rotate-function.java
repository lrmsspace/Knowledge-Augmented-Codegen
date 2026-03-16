// Source: https://leetcode.com/problems/rotate-function/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of length n.
//
// Assume arrk to be an array obtained by rotating nums by k positions clock-wise. We define the rotation function F on nums as follow:
//
//
// 	F(k) = 0 * arrk[0] + 1 * arrk[1] + ... + (n - 1) * arrk[n - 1].
//
//
// Return the maximum value of F(0), F(1), ..., F(n-1).
//
// The test cases are generated so that the answer fits in a 32-bit integer.
//
// Example:
// Input: nums = [4,3,2,6]
// Output: 26
// Explanation:
// F(0) = (0 * 4) + (1 * 3) + (2 * 2) + (3 * 6) = 0 + 3 + 4 + 18 = 25
// F(1) = (0 * 6) + (1 * 4) + (2 * 3) + (3 * 2) = 0 + 4 + 6 + 6 = 16
// F(2) = (0 * 2) + (1 * 6) + (2 * 4) + (3 * 3) = 0 + 6 + 8 + 9 = 23
// F(3) = (0 * 3) + (1 * 2) + (2 * 6) + (3 * 4) = 0 + 2 + 12 + 12 = 26
// So the maximum value of F(0), F(1), F(2), F(3) is F(3) = 26.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	-100 <= nums[i] <= 100
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Fenwick Tree (array, bit-fenwick, prefix-sum)
//   • When to use: When you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It is ideal for scenarios requiring both fast query and update operations on an array.
//   • Idea: A Fenwick tree, or Binary Indexed Tree (BIT), is an array-based data structure that efficiently calculates prefix sums and updates individual elements in an array. It supports both point updates and prefix sum queries in O(log N) time complexity.
//   • Invariants: Each `T[i]` stores the sum of a specific range `[g(i), i]` from the original array.; The `sum(idx)` function correctly aggregates values from `A[0]` to `A[idx]`.
//   • Tips: Understand the bit manipulation (`i & -i`) for navigating parent/child relationships.; Consistently choose and apply either 0-based or 1-based indexing throughout the implementation.
//   • Pitfalls: Incorrectly handling 0-based versus 1-based indexing can lead to off-by-one errors.; Forgetting to initialize the tree or performing updates incorrectly will yield wrong results.
// - Fibonacci Numbers (number, recursion, binary-lifting)
//   • When to use: Use when computing the N-th Fibonacci number for extremely large N, or when the result needs to be calculated modulo a specific value, requiring logarithmic time complexity.
//   • Idea: This method computes the N-th Fibonacci number by leveraging matrix exponentiation or specific doubling identities, reducing the problem size by half in each step. It achieves an O(log N) time complexity.
//   • Invariants: The function `compute(n)` always returns the pair `(F_n, F_{n+1})`.; For any `k`, the values `F_k` and `F_{k+1}` are correctly computed before deriving `F_{2k}` and `F_{2k+1}`.
//   • Tips: Utilize matrix exponentiation for a general and robust approach.; The doubling identities F_2k+1 and F_2k can be faster than explicit matrix multiplication.
//   • Pitfalls: Integer overflow if modulo arithmetic or arbitrary-precision integers are not used for large N.; Incorrectly defining base cases in the recursive implementation can lead to errors.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maxRotateFunction(int[] nums) {
        int n = nums.length;
        int sum = 0;
        int f0 = 0;

        for (int i = 0; i < n; i++) {
            sum += nums[i];
            f0 += i * nums[i];
        }

        int maxF = f0;
        int currentF = f0;

        for (int k = 1; k < n; k++) {
            currentF = currentF + sum - n * nums[n - k];
            maxF = Math.max(maxF, currentF);
        }

        return maxF;            
    }
}
