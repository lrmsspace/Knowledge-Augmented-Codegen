// Source: https://leetcode.com/problems/minimum-lines-to-represent-a-line-chart/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array stockPrices where stockPrices[i] = [dayi, pricei] indicates the price of the stock on day dayi is pricei. A line chart is created from the array by plotting the points on an XY plane with the X-axis representing the day and the Y-axis representing the price and connecting adjacent points. One such example is shown below:
//
// Return the minimum number of lines needed to represent the line chart.
//
// Example:
// Input: stockPrices = [[1,7],[2,6],[3,5],[4,4],[5,4],[6,3],[7,2],[8,1]]
// Output: 3
// Explanation:
// The diagram above represents the input, with the X-axis representing the day and Y-axis representing the price.
// The following 3 lines can be drawn to represent the line chart:
// - Line 1 (in red) from (1,7) to (4,4) passing through (1,7), (2,6), (3,5), and (4,4).
// - Line 2 (in blue) from (4,4) to (5,4).
// - Line 3 (in green) from (5,4) to (8,1) passing through (5,4), (6,3), (7,2), and (8,1).
// It can be shown that it is not possible to represent the line chart using less than 3 lines.
//
// Constraints:
// 1 <= stockPrices.length <= 105
// 	stockPrices[i].length == 2
// 	1 <= dayi, pricei <= 109
// 	All dayi are distinct.
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Convex hull trick and Li Chao tree (number, segment-tree, recursion)
//   • When to use: Used to find the minimum (or maximum) value among a set of linear functions at a given point. It is particularly efficient for dynamic sets of lines or when slopes are monotonic.
//   • Idea: The Convex Hull Trick (CHT) and Li Chao Tree efficiently find the minimum (or maximum) value of a set of linear functions at a query point. CHT typically achieves O(log N) or O(1) amortized time, while Li Chao Tree offers O(log C) for updates and queries.
//   • Invariants: In CHT, the lower envelope of lines forms a convex shape, with slopes monotonically ordered.; In Li Chao Tree, each node stores a line that is optimal at the segment's midpoint for lines added to that node.
//   • Tips: Ensure slopes are monotonic for efficient CHT implementations.; Li Chao Tree handles non-monotonic slopes but requires a coordinate range.
//   • Pitfalls: Floating point precision issues can lead to incorrect intersection calculations.; Incorrectly managing the convex hull structure (e.g., deque) in CHT.
// - Convex Hull construction (geometry, array, stack, sweep-line, monotonic-stack)
//   • When to use: When you need to find the smallest convex polygon enclosing a given set of points. It's used for problems requiring the outermost boundary of a point set.
//   • Idea: Convex Hull construction algorithms, like Graham Scan or Monotone Chain, find the smallest convex polygon that encloses a given set of points. These algorithms typically have a time complexity of O(N log N) due to sorting.
//   • Invariants: The points currently on the stack form a convex chain in the desired direction.; For any three consecutive points A, B, C on the stack, the turn from AB to BC maintains convexity.
//   • Tips: Use an orientation test (cross product) to determine if points make a clockwise or counter-clockwise turn.; Handle collinear points carefully, especially if they need to be included in the hull.
//   • Pitfalls: Incorrectly handling collinear points can lead to an incomplete or incorrect hull.; Floating-point precision issues can affect orientation tests, leading to wrong turns.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minimumLines(vector<vector<int>>& stockPrices) {
        int n = stockPrices.size();
        if (n <= 2) return n - 1;

        // Sort by day
        sort(stockPrices.begin(), stockPrices.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[0] < b[0];
             });

        int lines = 1; // at least one line needed
        for (int i = 2; i < n; ++i) {
            // Check if points (i-2), (i-1), (i) are collinear
            long long x1 = stockPrices[i-2][0], y1 = stockPrices[i-2][1];
            long long x2 = stockPrices[i-1][0], y2 = stockPrices[i-1][1];
            long long x3 = stockPrices[i][0],   y3 = stockPrices[i][1];

            // Use cross product to check collinearity
            // (y2 - y1)*(x3 - x2) == (y3 - y2)*(x2 - x1)
            if ((y2 - y1) * (x3 - x2) != (y3 - y2) * (x2 - x1)) {
                ++lines;
            }
        }

        return lines;           
    }
};
