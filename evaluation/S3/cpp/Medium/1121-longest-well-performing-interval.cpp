// Source: https://leetcode.com/problems/longest-well-performing-interval/   |   Difficulty: Medium
//
// Problem Description:
// We are given hours, a list of the number of hours worked per day for a given employee.
//
// A day is considered to be a tiring day if and only if the number of hours worked is (strictly) greater than 8.
//
// A well-performing interval is an interval of days for which the number of tiring days is strictly larger than the number of non-tiring days.
//
// Return the length of the longest well-performing interval.
//
// Example:
// Input: hours = [9,9,6,0,6,6,9]
// Output: 3
// Explanation: The longest well-performing interval is [9,9,6].
//
// Constraints:
// 1 <= hours.length <= 104
// 	0 <= hours[i] <= 16
//
// Helpful references (internal KB):
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Continued fractions (number, array, enumeration)
//   • When to use: Use when representing real numbers as a sequence of integers for rational approximation, or when analyzing properties of irrational numbers. It's also useful for solving certain Diophantine equations and Pell's equation.
//   • Idea: Continued fractions represent a real number as a sum of an integer and the reciprocal of another number, which is then represented in the same way. This process generates a sequence of integers, and its complexity depends on the desired precision or the number's nature.
//   • Invariants: The current integer term `a_i` is `floor(x_i)`, where `x_i` is the current real value being expanded.; The next real value `x_{i+1}` is `1 / (x_i - a_i)` if `x_i - a_i` is non-zero.
//   • Tips: Understand the recursive definition of continued fractions.; The Euclidean algorithm forms the basis for computing finite continued fractions.
//   • Pitfalls: Floating-point precision issues can severely limit accuracy for irrational numbers.; Misinterpreting convergents as exact values instead of approximations.
// - Sqrt Decomposition (array, enumeration, prefix-sum)
//   • When to use: Use when frequent range queries and point/range updates are needed on an array, offering a balanced O(sqrt(N)) time complexity for both operations. It's a good alternative when a segment tree is too complex or overkill.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and updates. It achieves an O(sqrt(N)) time complexity for both query and update operations.
//   • Invariants: Each block maintains an up-to-date aggregate of its elements.; For any query, fully contained blocks are processed using their precomputed aggregates.
//   • Tips: Choose block size carefully, typically sqrt(N) for optimal balance.; Precompute block aggregates (sum, min, max) for efficient queries.
//   • Pitfalls: Incorrectly handling partial blocks or boundary conditions.; Off-by-one errors in block indices or element indices within blocks.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int n = hours.size();
        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + (hours[i] > 8 ? 1 : -1);
        }

        stack<int> st;
        for (int i = 0; i <= n; ++i) {
            if (st.empty() || prefix[st.top()] > prefix[i]) {
                st.push(i);
            }
        }

        int ans = 0;
        for (int i = n; i >= 0; --i) {
            while (!st.empty() && prefix[st.top()] < prefix[i]) {
                ans = max(ans, i - st.top());
                st.pop();
            }
        }
        return ans;         
    }
};
