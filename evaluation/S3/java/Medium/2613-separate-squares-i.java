// Source: https://leetcode.com/problems/separate-squares-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array squares. Each squares[i] = [xi, yi, li] represents the coordinates of the bottom-left point and the side length of a square parallel to the x-axis.
//
// Find the minimum y-coordinate value of a horizontal line such that the total area of the squares above the line equals the total area of the squares below the line.
//
// Answers within 10-5 of the actual answer will be accepted.
//
// Note: Squares may overlap. Overlapping areas should be counted multiple times.
//
// Example:
// Input: squares = [[0,0,1],[2,2,1]]
//
// Output: 1.00000
//
// Explanation:
//
//
//
// Any horizontal line between y = 1 and y = 2 will have 1 square unit above it and 1 square unit below it. The lowest option is 1.
//
// Constraints:
// 1 <= squares.length <= 5 * 104
// 	squares[i] = [xi, yi, li]
// 	squares[i].length == 3
// 	0 <= xi, yi <= 109
// 	1 <= li <= 109
// 	The total area of all the squares will not exceed 1012.
//
// Helpful references (internal KB):
// - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
//   • When to use: When you need to calculate the area of a simple polygon given its vertices in sequential order. It efficiently handles both convex and non-convex polygons.
//   • Idea: This algorithm calculates the area of a simple polygon by summing the signed areas of trapezoids or triangles formed by its edges and a reference point/axis. It achieves O(N) time complexity.
//   • Invariants: The sum accumulates the signed area contribution of processed edges.; The current vertex and the next vertex define an edge of the polygon.
//   • Tips: Ensure vertices are provided in sequential order (clockwise or counter-clockwise).; The absolute value of the final result is the polygon's area.
//   • Pitfalls: Supplying vertices in a non-sequential or arbitrary order will yield an incorrect area.; Applying the formula to self-intersecting polygons will not give the true geometric area.
// - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
//   • When to use: Use when calculating the area of a simple polygon given its vertices in order. It is efficient for both convex and non-convex polygons.
//   • Idea: This algorithm calculates the area of a simple polygon by summing signed trapezoidal areas formed by each edge and the x-axis, or equivalently, using the shoelace formula. It achieves an optimal O(N) time complexity, where N is the number of vertices.
//   • Invariants: Vertices are processed sequentially in their given order, forming edges.; The running sum `current_sum` accumulates the signed contribution from each edge processed so far.
//   • Tips: Ensure vertices are provided in a consistent order (clockwise or counter-clockwise).; Use a data type with sufficient range (e.g., long long or double) for intermediate sums to prevent overflow.
//   • Pitfalls: Incorrect vertex order will result in an incorrect signed area or even zero.; Integer overflow can occur if coordinates are large and sums exceed standard integer limits.
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public double separateSquares(int[][] squares) {
        // Step 1: Collect all unique y-coordinates (start and end of squares)
        TreeSet<Integer> yCoords = new TreeSet<>();
        for (int[] square : squares) {
            int yStart = square[1];
            int yEnd = square[1] + square[2];
            yCoords.add(yStart);
            yCoords.add(yEnd);
        }

        // Step 2: Create a list of events for the sweep line
        List<Event> events = new ArrayList<>();
        for (int[] square : squares) {
            int xStart = square[0];
            int xEnd = square[0] + square[2];
            int yStart = square[1];
            int yEnd = square[1] + square[2];
            events.add(new Event(xStart, yStart, yEnd, 1)); // Start of a square
            events.add(new Event(xEnd, yStart, yEnd, -1));  // End of a square
        }
        events.sort(Comparator.comparingInt(e -> e.x)); // Sort by x-coordinate

        // Step 3: Sweep line to calculate area above and below each horizontal line
        double totalAreaAbove = 0;
        double totalAreaBelow = 0;
        int activeCount = 0;
        int prevX = 0;

        for (Event event : events) {
            if (activeCount > 0) {
                double width = event.x - prevX;
                double heightAbove = getHeightAbove(event.yStart, event.yEnd, yCoords);
                double heightBelow = getHeightBelow(event.yStart, event.yEnd, yCoords);
                totalAreaAbove += width * heightAbove;
                totalAreaBelow += width * heightBelow;
            }
            activeCount += event.type; // Update active count
            prevX = event.x; // Move to the next x-coordinate
        }

        // Step 4: Find the minimum y-coordinate that balances the areas
        double low = 0;
        double high = Collections.max(yCoords) + 1; // A value above all squares
        while (high - low > 1e-5) {
            double mid = low + (high - low) / 2;
            if (getAreaAbove(mid, squares) < getAreaBelow(mid, squares)) {
                low = mid; // Move up           
            } else {
                high = mid; // Move down
            }
        }
        return low; // or high, they are close enough
    }
}
