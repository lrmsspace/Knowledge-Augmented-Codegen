// Source: https://leetcode.com/problems/maximum-frequency-after-subarray-operation/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums of length n. You are also given an integer k.
//
// You perform the following operation on nums once:
//
//
// 	Select a subarray nums[i..j] where 0 <= i <= j <= n - 1.
// 	Select an integer x and add x to all the elements in nums[i..j].
//
//
// Find the maximum frequency of the value k after the operation.
//
// Example:
// Input: nums = [1,2,3,4,5,6], k = 1
//
// Output: 2
//
// Explanation:
//
// After adding -5 to nums[2..5], 1 has a frequency of 2 in [1, 2, -2, -1, 0, 1].
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	1 <= nums[i] <= 50
// 	1 <= k <= 50
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Linear Diophantine Equation (number, interval, enumeration)
//   • When to use: Use when you need to find or count all integer solutions (x, y) for a linear Diophantine equation ax + by = c, especially when solutions are constrained within specific intervals for x and y.
//   • Idea: This method finds all integer solutions to a linear Diophantine equation ax + by = c within given x and y intervals. It first finds a particular solution, then uses properties of the general solution to determine the valid range for x, and enumerates solutions in O(N) time where N is the number of solutions.
//   • Invariants: The current (x, y) pair always satisfies the linear Diophantine equation ax + by = c.; The current x value is an integer and satisfies the effective bounds l_x <= x <= r_x.
//   • Tips: Pre-divide coefficients a, b, c by gcd(a, b) to simplify the equation.; Use the Extended Euclidean Algorithm to find an initial particular solution (x0, y0).
//   • Pitfalls: Failing to check if c is divisible by gcd(a, b) before proceeding, leading to incorrect results.; Incorrectly applying the shifting logic for x and y bounds, resulting in an invalid solution range.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        int count[51] = {0};
        for (int num : nums) {
            count[num]++;
        }

        int maxFreq = 0;
        for (int val = 1; val <= 50; ++val) {
            int freq = count[val];
            int remK = k;

            // Try to increase frequency by converting other numbers to 'val'
            for (int diff = 1; diff <= 50; ++diff) {
                // Check lower numbers
                if (val - diff >= 1) {
                    int canConvert = remK / diff;
                    int toConvert = (canConvert < count[val - diff]) ? canConvert : count[val - diff];
                    freq += toConvert;
                    remK -= toConvert * diff;
                }
                // Check higher numbers
                if (val + diff <= 50) {
                    int canConvert = remK / diff;
                    int toConvert = (canConvert < count[val + diff]) ? canConvert : count[val + diff];
                    freq += toConvert;
                    remK -= toConvert * diff;
                }
                if (remK <= 0) break;
            }
            if (freq > maxFreq) {
                maxFreq = freq;
            }
        }

        return maxFreq;         
    }
};
