// Source: https://leetcode.com/problems/minimum-rectangles-to-cover-points/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array points, where points[i] = [xi, yi]. You are also given an integer w. Your task is to cover all the given points with rectangles.
//
// Each rectangle has its lower end at some point (x1, 0) and its upper end at some point (x2, y2), where x1 <= x2, y2 >= 0, and the condition x2 - x1 <= w must be satisfied for each rectangle.
//
// A point is considered covered by a rectangle if it lies within or on the boundary of the rectangle.
//
// Return an integer denoting the minimum number of rectangles needed so that each point is covered by at least one rectangle.
//
// Note: A point may be covered by more than one rectangle.
//
// Example:
// Input: points = [[2,1],[1,0],[1,4],[1,8],[3,5],[4,6]], w = 1
//
// Output: 2
//
// Explanation: 
//
// The image above shows one possible placement of rectangles to cover the points:
//
//
// 	A rectangle with a lower end at (1, 0) and its upper end at (2, 8)
// 	A rectangle with a lower end at (3, 0) and its upper end at (4, 8)
//
// Constraints:
// 1 <= points.length <= 105
// 	points[i].length == 2
// 	0 <= xi == points[i][0] <= 109
// 	0 <= yi == points[i][1] <= 109
// 	0 <= w <= 109
// 	All pairs (xi, yi) are distinct.
//
// Helpful references (internal KB):
// - Finding the nearest pair of points (geometry, array, divide-and-conquer)
//   • When to use: Use this algorithm to efficiently find the pair of points with the minimum Euclidean distance among a given set of N points in a 2D plane. It is particularly effective for large datasets where an O(N^2) approach is too slow.
//   • Idea: This divide-and-conquer algorithm finds the closest pair of points in a 2D plane by recursively splitting the set of points and merging results. It achieves an optimal time complexity of O(N log N).
//   • Invariants: At the start of any recursive call, the input point set is sorted by X-coordinate.; The returned minimum distance 'd' for a subproblem is the true minimum distance among its points.
//   • Tips: Initial sorting by X-coordinate is crucial for efficient division of the point set.; Handle base cases (e.g., 2 or 3 points) with a simple brute-force distance calculation.
//   • Pitfalls: Forgetting to sort points by Y-coordinate within the central strip can degrade performance to O(N^2).; Incorrectly defining the strip width or comparison range in the merge step can lead to incorrect results.
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Lattice points inside non-lattice polygon (geometry, number, counting, recursion)
//   • When to use: Use this when you need to count integer coordinate points strictly inside a polygon whose vertices are not restricted to integer coordinates. It's suitable for problems requiring precise geometric counting with non-lattice boundaries.
//   • Idea: This algorithm counts lattice points within a polygon with arbitrary vertices by summing signed contributions from each edge. It reduces the problem to evaluating sums of floor functions, sum(floor(kx+b)), which is solved recursively, typically achieving logarithmic complexity per edge.
//   • Invariants: The sum sum(floor(kx+b)) correctly accumulates points below the current edge segment.; After coordinate transformations, the problem reduces to a sum over a non-negative range with non-negative k and b.
//   • Tips: Decompose the polygon into signed areas under each edge, similar to the shoelace formula.; Handle edge cases where k or b are negative by appropriate transformations.
//   • Pitfalls: Floating point precision issues when calculating k and b or during transformations.; Incorrectly handling boundary points (points on edges or vertices).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minRectanglesToCoverPoints(vector<vector<int>>& points, int w) {
        // Sort points by x-coordinate
        sort(points.begin(), points.end());
        int n = points.size();
        int rectangles = 0;
        int i = 0;

        while (i < n) {
            // Start a new rectangle
            rectangles++;
            int rect_start = points[i][0];
            int rect_end = rect_start + w;

            // Move i to cover all points within this rectangle
            while (i < n && points[i][0] <= rect_end) {
                i++;
            }
        }

        return rectangles;          
    }
};
