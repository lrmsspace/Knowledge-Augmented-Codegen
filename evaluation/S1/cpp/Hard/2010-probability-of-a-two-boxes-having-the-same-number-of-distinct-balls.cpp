// Source: https://leetcode.com/problems/probability-of-a-two-boxes-having-the-same-number-of-distinct-balls/   |   Difficulty: Hard
//
// Problem Description:
// Given 2n balls of k distinct colors. You will be given an integer array balls of size k where balls[i] is the number of balls of color i.
//
// All the balls will be shuffled uniformly at random, then we will distribute the first n balls to the first box and the remaining n balls to the other box (Please read the explanation of the second example carefully).
//
// Please note that the two boxes are considered different. For example, if we have two balls of colors a and b, and two boxes [] and (), then the distribution [a] (b) is considered different than the distribution [b] (a) (Please read the explanation of the first example carefully).
//
// Return the probability that the two boxes have the same number of distinct balls. Answers within 10-5 of the actual value will be accepted as correct.
//
// Example:
// Input: balls = [1,1]
// Output: 1.00000
// Explanation: Only 2 ways to divide the balls equally:
// - A ball of color 1 to box 1 and a ball of color 2 to box 2
// - A ball of color 2 to box 1 and a ball of color 1 to box 2
// In both ways, the number of distinct colors in each box is equal. The probability is 2/2 = 1
//
// Constraints:
// 1 <= balls.length <= 8
// 	1 <= balls[i] <= 6
// 	sum(balls) is even.
//
// Helpful references (internal KB):
// - Binomial Coefficients (array, dp-2d)
//   • When to use: Use when you need to compute many binomial coefficients, especially for values up to a certain N, or when working with modulo arithmetic where division is not straightforward.
//   • Idea: This method computes binomial coefficients using Pascal's identity, building a 2D DP table where C(n, k) = C(n-1, k-1) + C(n-1, k). It has a time complexity of O(N^2) for computing all coefficients up to N.
//   • Invariants: For each cell dp[i][j], it stores the value of C(i, j).; At the start of computing row i, all values for row i-1 are correctly calculated and available.
//   • Tips: Optimize space by storing only the current and previous row of the DP table.; For O(1) lookup after precomputation, calculate all factorials and inverse factorials modulo a prime.
//   • Pitfalls: Direct division for C(n,k) = n! / (k!(n-k)!) is problematic with modulo arithmetic unless the modulo is prime.; Integer overflow can occur for large N and K if not handled with appropriate data types or modulo operations.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    double getProbability(vector<int>& balls) {
        int k = balls.size();
        int n = 0;
        for (int b : balls) n += b;
        n /= 2;

        vector<vector<double>> comb(n + 1, vector<double>(n + 1, 0.0));
        comb[0][0] = 1.0;
        for (int i = 1; i <= n; ++i) {
            comb[i][0] = 1.0;
            for (int j = 1; j <= i; ++j) {
                comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
            }
        }

        double totalWays = 0.0;
        double validWays = 0.0;

        function<void(int, int, int, int, double)> backtrack =
            [&](int colorIdx, int box1Count, int box2Count, int distinct1, int distinct2, double ways) {
                if (colorIdx == k) {
                    if (box1Count == n && box2Count == n) {
                        totalWays += ways;
                        if (distinct1 == distinct2) {
                            validWays += ways;
                        }
                    }
                    return;
                }

                for (int c1 = 0; c1 <= balls[colorIdx]; ++c1) {
                    int c2 = balls[colorIdx] - c1;
                    if (box1Count + c1 > n || box2Count + c2 > n) continue;

                    int newDistinct1 = distinct1 + (c1 > 0 ? 1 : 0);
                    int newDistinct2 = distinct2 + (c2 > 0 ? 1 : 0);
                    double newWays = ways * comb[balls[colorIdx]][c1];

                    backtrack(colorIdx + 1, box1Count + c1, box2Count + c2,
                              newDistinct1, newDistinct2, newWays);
                }
            };

        backtrack(0, 0, 0, 0, 0, 1.0);

        return validWays / totalWays;           
    }
};
