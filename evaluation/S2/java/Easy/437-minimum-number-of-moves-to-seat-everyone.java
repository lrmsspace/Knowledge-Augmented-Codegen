// Source: https://leetcode.com/problems/minimum-number-of-moves-to-seat-everyone/   |   Difficulty: Easy
//
// Problem Description:
// There are n availabe seats and n students standing in a room. You are given an array seats of length n, where seats[i] is the position of the ith seat. You are also given the array students of length n, where students[j] is the position of the jth student.
//
// You may perform the following move any number of times:
//
//
// 	Increase or decrease the position of the ith student by 1 (i.e., moving the ith student from position x to x + 1 or x - 1)
//
//
// Return the minimum number of moves required to move each student to a seat such that no two students are in the same seat.
//
// Note that there may be multiple seats or students in the same position at the beginning.
//
// Example:
// Input: seats = [3,1,5], students = [2,7,4]
// Output: 4
// Explanation: The students are moved as follows:
// - The first student is moved from position 2 to position 1 using 1 move.
// - The second student is moved from position 7 to position 5 using 2 moves.
// - The third student is moved from position 4 to position 3 using 1 move.
// In total, 1 + 2 + 1 = 4 moves were used.
//
// Constraints:
// n == seats.length == students.length
// 	1 <= n <= 100
// 	1 <= seats[i], students[j] <= 100
//
// Helpful references (internal KB):
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
// - Solving assignment problem using min-cost-flow (graph, dijkstra, bellman-ford)
//   • When to use: Use when finding a one-to-one assignment between two sets of entities, such as workers to tasks, to minimize the total cost. It's suitable for problems modelable as min-cost max-flow in a bipartite graph.
//   • Idea: This technique models the assignment problem as a minimum cost maximum flow problem on a specially constructed bipartite graph. It finds a perfect matching with the lowest total cost, typically with a polynomial time complexity depending on the shortest path algorithm used.
//   • Invariants: Flow conservation holds for all intermediate nodes in the network.; The flow on any edge never exceeds its defined capacity.
//   • Tips: Construct a bipartite graph with a source and sink nodes.; Set capacities to 1 for all assignment-related edges to ensure one-to-one mapping.
//   • Pitfalls: Incorrectly modeling capacities or costs on graph edges can lead to wrong solutions.; Forgetting to ensure a perfect matching (flow value equals N) is found for a complete assignment.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minMovesToSeat(int[] seats, int[] students) {
        Arrays.sort(seats);
        Arrays.sort(students);

        int moves = 0;
        for (int i = 0; i < seats.length; i++) {
            moves += Math.abs(seats[i] - students[i]);
        }

        return moves;           
    }
}
