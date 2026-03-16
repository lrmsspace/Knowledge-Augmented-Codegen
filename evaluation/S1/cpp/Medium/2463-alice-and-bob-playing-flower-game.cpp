// Source: https://leetcode.com/problems/alice-and-bob-playing-flower-game/   |   Difficulty: Medium
//
// Problem Description:
// Alice and Bob are playing a turn-based game on a field, with two lanes of flowers between them. There are x flowers in the first lane between Alice and Bob, and y flowers in the second lane between them.
//
//
//
// The game proceeds as follows:
//
//
// 	Alice takes the first turn.
// 	In each turn, a player must choose either one of the lane and pick one flower from that side.
// 	At the end of the turn, if there are no flowers left at all in either lane, the current player captures their opponent and wins the game.
//
//
// Given two integers, n and m, the task is to compute the number of possible pairs (x, y) that satisfy the conditions:
//
//
// 	Alice must win the game according to the described rules.
// 	The number of flowers x in the first lane must be in the range [1,n].
// 	The number of flowers y in the second lane must be in the range [1,m].
//
//
// Return the number of possible pairs (x, y) that satisfy the conditions mentioned in the statement.
//
// Example:
// Input: n = 3, m = 2
// Output: 3
// Explanation: The following pairs satisfy conditions described in the statement: (1,2), (3,2), (2,1).
//
// Constraints:
// 1 <= n, m <= 105
//
// Helpful references (internal KB):
// - Linear Diophantine Equation (number, interval, enumeration)
//   • When to use: Use when you need to find or count all integer solutions (x, y) for a linear Diophantine equation ax + by = c, especially when solutions are constrained within specific intervals for x and y.
//   • Idea: This method finds all integer solutions to a linear Diophantine equation ax + by = c within given x and y intervals. It first finds a particular solution, then uses properties of the general solution to determine the valid range for x, and enumerates solutions in O(N) time where N is the number of solutions.
//   • Invariants: The current (x, y) pair always satisfies the linear Diophantine equation ax + by = c.; The current x value is an integer and satisfies the effective bounds l_x <= x <= r_x.
//   • Tips: Pre-divide coefficients a, b, c by gcd(a, b) to simplify the equation.; Use the Extended Euclidean Algorithm to find an initial particular solution (x0, y0).
//   • Pitfalls: Failing to check if c is divisible by gcd(a, b) before proceeding, leading to incorrect results.; Incorrectly applying the shifting logic for x and y bounds, resulting in an invalid solution range.
// - The Inclusion-Exclusion Principle (number, counting)
//   • When to use: Used for counting elements that satisfy a specific number of conditions (exactly k, at least k) from a larger set of conditions. It is particularly effective when direct counting with overlapping properties is complex.
//   • Idea: The Inclusion-Exclusion Principle is a combinatorial technique to count the size of a union of sets by summing the sizes of individual sets, then adjusting for intersections. For problems involving 'k' conditions, optimized versions can achieve O(2^N * N) complexity, where N is the total number of conditions.
//   • Invariants: The current sum correctly reflects the inclusion-exclusion contribution for all processed subsets of conditions.; Each f(Y) term accurately represents the count of elements satisfying at least all conditions in Y.
//   • Tips: Clearly define the sets and conditions involved in the problem.; Remember the alternating signs for sums of intersections.
//   • Pitfalls: Incorrectly applying the alternating signs in the summation.; Miscalculating the sizes of intersections (f(Y) terms).
// - Counting labeled graphs (number, recursion, counting, dp-1d)
//   • When to use: When the problem requires enumerating distinct labeled graphs with specific properties, such as connectivity, on a given number of vertices. It is suitable for combinatorial counting problems involving graph structures.
//   • Idea: This technique determines the number of connected labeled graphs by subtracting the count of disconnected graphs from the total. It typically employs a recursive or dynamic programming approach, often involving combinatorial terms like binomial coefficients, with a polynomial time complexity.
//   • Invariants: The total number of labeled graphs $G_n$ for $n$ vertices is always $2^{n(n-1)/2}$.; For any $n$, the sum of connected and disconnected labeled graphs equals the total number of labeled graphs.
//   • Tips: Start with the total number of labeled graphs $G_n = 2^{n(n-1)/2}$.; Use complementary counting: total graphs minus disconnected graphs.
//   • Pitfalls: Forgetting to divide by $n$ when converting from rooted to unrooted disconnected graphs.; Incorrectly handling base cases for recursive definitions or DP states.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long flowerGame(int n, int m) {
        long long total = (long long)n * m;
        long long lose = (long long)(n / 2) * (m / 2);
        return total - lose;            
    }
};
