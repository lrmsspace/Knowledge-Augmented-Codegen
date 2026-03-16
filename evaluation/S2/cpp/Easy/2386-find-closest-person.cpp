// Source: https://leetcode.com/problems/find-closest-person/   |   Difficulty: Easy
//
// Problem Description:
// You are given three integers x, y, and z, representing the positions of three people on a number line:
//
//
// 	x is the position of Person 1.
// 	y is the position of Person 2.
// 	z is the position of Person 3, who does not move.
//
//
// Both Person 1 and Person 2 move toward Person 3 at the same speed.
//
// Determine which person reaches Person 3 first:
//
//
// 	Return 1 if Person 1 arrives first.
// 	Return 2 if Person 2 arrives first.
// 	Return 0 if both arrive at the same time.
//
//
// Return the result accordingly.
//
// Example:
// Input: x = 2, y = 7, z = 4
//
// Output: 1
//
// Explanation:
//
//
// 	Person 1 is at position 2 and can reach Person 3 (at position 4) in 2 steps.
// 	Person 2 is at position 7 and can reach Person 3 in 3 steps.
//
//
// Since Person 1 reaches Person 3 first, the output is 1.
//
// Constraints:
// 1 <= x, y, z <= 100
//
// Helpful references (internal KB):
// - Finding the equation of a line for a segment (number, geometry, gcd)
//   • When to use: Use this method when you need to represent a line segment's equation using integer coefficients, especially to avoid floating-point inaccuracies in geometric computations.
//   • Idea: This method derives the general form of a line equation (Ax + By + C = 0) from two points, ensuring integer coefficients if input coordinates are integers. It then normalizes these coefficients using GCD to achieve a unique representation, typically in O(log(max(|A|,|B|,|C|))) time due to GCD.
//   • Invariants: The calculated coefficients A, B, C always satisfy A*Px + B*Py + C = 0 for point P(Px, Py).; After GCD division, the absolute values of A, B, C are coprime (unless all are zero).
//   • Tips: Always compute A, B, C using the given formulas for P(Px, Py) and Q(Qx, Qy).; Use absolute values of A, B, C when calculating their greatest common divisor.
//   • Pitfalls: Forgetting to normalize coefficients leads to non-unique representations for the same line.; Incorrectly handling signs during the final normalization step can result in inconsistent forms.
// - 0-1 BFS (graph, deque, 01-bfs, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently computes single-source shortest paths, outperforming Dijkstra's for this specific weight constraint.
//   • Idea: 0-1 BFS is a graph traversal algorithm that finds the single-source shortest paths in a graph where all edge weights are restricted to 0 or 1. It uses a deque to process nodes, achieving an optimal time complexity of O(V + E).
//   • Invariants: When a node 'u' is extracted from the front of the deque, 'dist[u]' is its shortest path from the source.; The deque always contains nodes whose distances are either 'D' or 'D+1', where 'D' is the distance of the last node extracted.
//   • Tips: Always push 0-weight edges to the front of the deque.; Push 1-weight edges to the back of the deque.
//   • Pitfalls: Pushing 0-weight edges to the back or 1-weight edges to the front of the deque.; Not correctly initializing distances or the source node.
// - Ternary Search (interval, number, binary-search, greedy)
//   • When to use: Use when searching for the extremum (maximum or minimum) of a unimodal function over a continuous or discrete interval. It efficiently narrows down the search space by evaluating the function at two internal points.
//   • Idea: Ternary search is a divide and conquer algorithm that finds the extremum of a unimodal function within an interval by repeatedly reducing the search space by approximately one-third. It has a logarithmic time complexity, similar to binary search, but requires two function evaluations per step.
//   • Invariants: The extremum of the unimodal function lies within the current interval [l, r].; The function value at m1 is compared with the function value at m2.
//   • Tips: Handle discrete intervals by checking remaining points when interval size is small.; Consider Golden Section Search to reduce function evaluations per iteration.
//   • Pitfalls: Incorrectly applying to non-unimodal functions.; Infinite loops if stopping condition for discrete intervals is not handled.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int findClosest(int x, int y, int z) {
        int dist1 = abs(x - z);
        int dist2 = abs(y - z);

        if (dist1 < dist2) {
            return 1; // Person 1 is closer
        } else if (dist2 < dist1) {
            return 2; // Person 2 is closer
        } else {
            return 0; // Both are equidistant
        }           
    }
};
