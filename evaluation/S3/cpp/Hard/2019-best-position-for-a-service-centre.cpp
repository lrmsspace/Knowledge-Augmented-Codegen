// Source: https://leetcode.com/problems/best-position-for-a-service-centre/   |   Difficulty: Hard
//
// Problem Description:
// A delivery company wants to build a new service center in a new city. The company knows the positions of all the customers in this city on a 2D-Map and wants to build the new center in a position such that the sum of the euclidean distances to all customers is minimum.
//
// Given an array positions where positions[i] = [xi, yi] is the position of the ith customer on the map, return the minimum sum of the euclidean distances to all customers.
//
// In other words, you need to choose the position of the service center [xcentre, ycentre] such that the following formula is minimized:
//
// Answers within 10-5 of the actual value will be accepted.
//
// Example:
// Input: positions = [[0,1],[1,0],[1,2],[2,1]]
// Output: 4.00000
// Explanation: As shown, you can see that choosing [xcentre, ycentre] = [1, 1] will make the distance to each customer = 1, the sum of all distances is 4 which is the minimum possible we can achieve.
//
// Constraints:
// 1 <= positions.length <= 50
// 	positions[i].length == 2
// 	0 <= xi, yi <= 100
//
// Helpful references (internal KB):
// - Ternary Search (number, binary-search)
//   • When to use: Use when searching for the minimum or maximum of a unimodal function over a continuous interval. It efficiently narrows down the search space by evaluating the function at two internal points.
//   • Idea: Ternary search is an optimization algorithm for finding the extremum (minimum or maximum) of a unimodal function within a given interval. It repeatedly reduces the search interval by two-thirds, achieving logarithmic time complexity with respect to the interval size.
//   • Invariants: The global extremum of the unimodal function within the initial range is always contained within the current interval [L, R].; The interval [L, R] is non-empty and its length strictly decreases in each iteration.
//   • Tips: Carefully define the search interval [L, R] for the function.; Choose two internal points, typically L + (R-L)/3 and R - (R-L)/3.
//   • Pitfalls: Applying to non-unimodal functions yields incorrect results.; Floating-point precision issues can lead to infinite loops or incorrect bounds.
// - Ternary Search (interval, number, binary-search, enumeration)
//   • When to use: Use Ternary Search to find the minimum or maximum of a unimodal or bitonic function over a continuous or discrete interval. It is effective when the function's derivative is hard to compute or unavailable.
//   • Idea: Ternary search is a divide and conquer algorithm that repeatedly narrows down the search space for the extremum of a unimodal function by evaluating two points within the current interval. It reduces the search interval by one-third in each step, achieving O(log N) time complexity.
//   • Invariants: The extremum of the unimodal function lies within the current interval [l, r].; The function value at m1 is compared with m2 to narrow the search.
//   • Tips: Ensure the function is strictly unimodal or bitonic within the search range.; Handle floating-point precision carefully for continuous functions.
//   • Pitfalls: Applying to non-unimodal functions yields incorrect results.; Floating-point errors can lead to incorrect bounds or infinite loops.
// - Finding the nearest pair of points (geometry, array, divide-and-conquer)
//   • When to use: Use this algorithm to efficiently find the pair of points with the minimum Euclidean distance among a given set of N points in a 2D plane. It is particularly effective for large datasets where an O(N^2) approach is too slow.
//   • Idea: This divide-and-conquer algorithm finds the closest pair of points in a 2D plane by recursively splitting the set of points and merging results. It achieves an optimal time complexity of O(N log N).
//   • Invariants: At the start of any recursive call, the input point set is sorted by X-coordinate.; The returned minimum distance 'd' for a subproblem is the true minimum distance among its points.
//   • Tips: Initial sorting by X-coordinate is crucial for efficient division of the point set.; Handle base cases (e.g., 2 or 3 points) with a simple brute-force distance calculation.
//   • Pitfalls: Forgetting to sort points by Y-coordinate within the central strip can degrade performance to O(N^2).; Incorrectly defining the strip width or comparison range in the merge step can lead to incorrect results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    double getMinDistSum(vector<vector<int>>& positions) {
        double x = 0, y = 0;
        for (const auto& pos : positions) {
            x += pos[0];
            y += pos[1];
        }
        int n = positions.size();
        x /= n;
        y /= n;

        double step = 100.0, ans = 1e18;
        while (step > 1e-5) {
            ans = min(ans, getDist(positions, x, y));
            double bestX = x, bestY = y;
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    double newX = x + i * step, newY = y + j * step;
                    double distSum = getDist(positions, newX, newY);
                    if (distSum < ans) {
                        ans = distSum;
                        bestX = newX;
                        bestY = newY;
                    }
                }
            }
            x = bestX;
            y = bestY;
            step *= 0.5;
        }
        return ans;
    }
};
