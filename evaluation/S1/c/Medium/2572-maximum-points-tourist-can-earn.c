// Source: https://leetcode.com/problems/maximum-points-tourist-can-earn/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers, n and k, along with two 2D integer arrays, stayScore and travelScore.
//
// A tourist is visiting a country with n cities, where each city is directly connected to every other city. The tourist's journey consists of exactly k 0-indexed days, and they can choose any city as their starting point.
//
// Each day, the tourist has two choices:
//
//
// 	Stay in the current city: If the tourist stays in their current city curr during day i, they will earn stayScore[i][curr] points.
// 	Move to another city: If the tourist moves from their current city curr to city dest, they will earn travelScore[curr][dest] points.
//
//
// Return the maximum possible points the tourist can earn.
//
// Example:
// Input: n = 2, k = 1, stayScore = [[2,3]], travelScore = [[0,2],[1,0]]
//
// Output: 3
//
// Explanation:
//
// The tourist earns the maximum number of points by starting in city 1 and staying in that city.
//
// Constraints:
// 1 <= n <= 200
// 	1 <= k <= 200
// 	n == travelScore.length == travelScore[i].length == stayScore[i].length
// 	k == stayScore.length
// 	1 <= stayScore[i][j] <= 100
// 	0 <= travelScore[i][j] <= 100
// 	travelScore[i][i] == 0
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxScore(int n, int k, int** stayScore, int stayScoreSize, int* stayScoreColSize, int** travelScore, int travelScoreSize, int* travelScoreColSize) {
    int dp[k][n];
    for (int city = 0; city < n; city++) {
        dp[0][city] = stayScore[0][city];
    }

    for (int day = 1; day < k; day++) {
        for (int currCity = 0; currCity < n; currCity++) {
            int maxPoints = dp[day - 1][currCity] + stayScore[day][currCity];
            for (int destCity = 0; destCity < n; destCity++) {
                if (destCity != currCity) {
                    int points = dp[day - 1][currCity] + travelScore[currCity][destCity] + stayScore[day][destCity];
                    if (points > maxPoints) {
                        maxPoints = points;
                    }
                }
            }
            dp[day][currCity] = maxPoints;
        }
    }

    int result = 0;
    for (int city = 0; city < n; city++) {
        if (dp[k - 1][city] > result) {
            result = dp[k - 1][city];
        }
    }

    return result;      
}
