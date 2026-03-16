// Source: https://leetcode.com/problems/separate-squares-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array squares. Each squares[i] = [xi, yi, li] represents the coordinates of the bottom-left point and the side length of a square parallel to the x-axis.
//
// Find the minimum y-coordinate value of a horizontal line such that the total area covered by squares above the line equals the total area covered by squares below the line.
//
// Answers within 10-5 of the actual answer will be accepted.
//
// Note: Squares may overlap. Overlapping areas should be counted only once in this version.
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
// Any horizontal line between y = 1 and y = 2 results in an equal split, with 1 square unit above and 1 square unit below. The minimum y-value is 1.
//
// Constraints:
// 1 <= squares.length <= 5 * 104
// 	squares[i] = [xi, yi, li]
// 	squares[i].length == 3
// 	0 <= xi, yi <= 109
// 	1 <= li <= 109
// 	The total area of all the squares will not exceed 1015.
//
// Helpful references (internal KB):
// - Search for a pair of intersecting segments (tree, geometry, sweep-line, counting)
//   • When to use: Use this algorithm to efficiently determine if any pair of line segments in a given set intersect. It is particularly effective for detecting geometric overlaps in a 2D plane.
//   • Idea: This algorithm processes segments by sweeping a vertical line across the plane, maintaining an ordered set of active segments to efficiently check for intersections with neighbors. It achieves an optimal time complexity of O(N log N).
//   • Invariants: The sweep line always moves from left to right, processing events in increasing x-coordinate order.; The set of active segments contains all segments currently intersected by the sweep line, ordered by their y-coordinate at the sweep line's current x-position.
//   • Tips: Process events at the same x-coordinate by adding segments before removing them to catch vertex intersections.; Use a balanced binary search tree (e.g., `std::set`) to maintain active segments, ordered by their y-coordinate.
//   • Pitfalls: Incorrect event ordering (e.g., removing before adding) can lead to missing intersections at shared endpoints.; Floating point precision issues can cause incorrect intersection detection or ordering of segments.
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Manhattan Distance (geometry, graph, sweep-line, mst-kruskal, coordinate-compress)
//   • When to use: Use this when finding the Minimum Spanning Tree for points in a 2D plane where edge weights are Manhattan distances, or when a geometric problem can be simplified by transforming Manhattan to Chebyshev distance.
//   • Idea: This algorithm finds the Minimum Spanning Tree for points in a 2D plane using Manhattan distance. It leverages a sweep-line approach to efficiently find nearest neighbors in specific octants, reducing the number of candidate edges for Kruskal's algorithm, achieving O(N log N) complexity.
//   • Invariants: For any point 's' in the active set, its nearest neighbor in the current octant has not yet been processed.; Points are processed in non-decreasing order of 'x + y' (or transformed coordinate), ensuring local optimality for distances.
//   • Tips: Consider transforming Manhattan distance problems into Chebyshev distance problems using (x+y, y-x) coordinates.; Divide the plane into 8 octants around each point to simplify nearest neighbor searches.
//   • Pitfalls: Incorrectly defining or handling the 8 octants, especially near boundaries or for points with equal coordinates.; Inefficiently managing the 'active set' during the sweep-line, leading to higher than O(N log N) complexity.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} squares
 * @return {number}
 */
var separateSquares = function(squares) {
    // Step 1: Create events for the sweep line
    const events = [];
    for (const [x, y, l] of squares) {
        events.push({ x, y, type: 'start', length: l });
        events.push({ x, y: y + l, type: 'end', length: l });
    }
    
    // Step 2: Sort events by x-coordinate
    events.sort((a, b) => a.x - b.x || (a.type === 'start' ? -1 : 1));

    // Step 3: Sweep line to calculate area above and below the line
    let active = [];
    let lastX = 0;
    let areaAbove = 0;
    let areaBelow = 0;

    for (const event of events) {
        const dx = event.x - lastX;
        if (dx > 0 && active.length > 0) {
            const heights = active.map(e => e.y + e.length);
            const minY = Math.min(...heights);
            const maxY = Math.max(...active.map(e => e.y));
            areaAbove += dx * Math.max(0, minY - maxY);
            areaBelow += dx * Math.max(0, maxY - minY);
        }

        if (event.type === 'start') {
            active.push(event);
        } else {
            active = active.filter(e => e !== event);
        }
        
        lastX = event.x;
    }

    // Step 4: Binary search for the minimum y-coordinate value
    let low = 0, high = 1e10;
    while (high - low > 1e-5) {
        const mid = (low + high) / 2;
        let areaAboveMid = 0;
        let areaBelowMid = 0;

        for (const [x, y, l] of squares) {
            const topY = y + l;
            if (topY > mid) {
                areaAboveMid += Math.max(0, topY - Math.max(y, mid)) * l;
            }
            if (y < mid) {
                areaBelowMid += Math.max(0, Math.min(mid, topY) - y) * l;
            }
        }

        if (areaAboveMid > areaBelowMid) {
            high = mid;
        } else {
            low = mid;
        }
    }

    return low;
};
