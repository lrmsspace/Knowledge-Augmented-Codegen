// Source: https://leetcode.com/problems/check-if-point-is-reachable/   |   Difficulty: Hard
//
// Problem Description:
// There exists an infinitely large grid. You are currently at point (1, 1), and you need to reach the point (targetX, targetY) using a finite number of steps.
//
// In one step, you can move from point (x, y) to any one of the following points:
//
//
// 	(x, y - x)
// 	(x - y, y)
// 	(2 * x, y)
// 	(x, 2 * y)
//
//
// Given two integers targetX and targetY representing the X-coordinate and Y-coordinate of your final position, return true if you can reach the point from (1, 1) using some number of steps, and false otherwise.
//
// Example:
// Input: targetX = 6, targetY = 9
// Output: false
// Explanation: It is impossible to reach (6,9) from (1,1) using any sequence of moves, so false is returned.
//
// Constraints:
// 1 <= targetX, targetY <= 109
//
// Helpful references (internal KB):
// - The Stern-Brocot tree and Farey sequences (number, tree, binary-search, simulation)
//   • When to use: Use this when representing positive rational numbers as unique paths in a binary tree or when efficiently approximating irrational numbers. It's ideal for finding a fraction's path or its position within ordered sequences.
//   • Idea: The Stern-Brocot tree uniquely maps every positive rational number to a binary path, constructed by repeatedly taking mediants. This allows for efficient search and representation of fractions with O(log(p+q)) time complexity.
//   • Invariants: The target fraction p/q always lies strictly between the current left boundary pL/qL and right boundary pR/qR.; The current left and right boundary fractions (pL/qL, pR/qR) are always adjacent terms in some Farey sequence.
//   • Tips: Initialize search boundaries with 0/1 and 1/0 (or 1/1 for positive fractions).; Calculate the mediant (pL+pR)/(qL+qR) to determine the next candidate fraction.
//   • Pitfalls: Naive O(p+q) search without run-length encoding can be too slow for large fractions.; Incorrectly handling initial boundary conditions (e.g., 0/1, 1/0, 1/1).
// - Check whether a graph is bipartite (graph, queue, bfs)
//   • When to use: Use this when you need to determine if an undirected graph can be divided into two independent sets such that all edges connect vertices from different sets, or if it is two-colorable.
//   • Idea: This algorithm determines if an undirected graph is bipartite by attempting to 2-color it using BFS. It assigns alternating colors (or sets) to adjacent vertices, detecting non-bipartite conditions if an edge connects two vertices of the same color.
//   • Invariants: All visited vertices within the current BFS component are correctly 2-colored.; All edges processed so far connect vertices of different colors.
//   • Tips: Use two distinct colors (e.g., 0 and 1) to represent the two sets.; Iterate through all vertices and start a new BFS from any unvisited vertex to handle disconnected components.
//   • Pitfalls: Forgetting to handle disconnected graphs by ensuring all vertices are visited.; Incorrectly assigning colors, leading to false positives or negatives.
// - Check if two segments intersect (geometry, number, simulation)
//   • When to use: Use this when determining if two line segments in a 2D plane share any common points, especially when floating-point precision issues need to be avoided.
//   • Idea: This algorithm determines if two line segments intersect by handling collinear and non-collinear cases separately, primarily using integer arithmetic to avoid precision errors. It typically runs in O(1) time.
//   • Invariants: If segments are collinear, their 1D projections on both axes must overlap for intersection.; If segments are not collinear, each segment's endpoints must lie on opposite sides of the line containing the other segment.
//   • Tips: Handle collinear segments as a distinct special case.; Utilize cross products for efficient orientation checks.
//   • Pitfalls: Failing to correctly identify and handle collinear segments.; Introducing floating-point errors by using division for slopes.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool isReachable(int targetX, int targetY) {
        // The problem can be solved by using the Stern-Brocot tree, which is a binary tree that represents all positive rational numbers. Each node in the tree corresponds to a fraction p/q, where p and q are positive integers. The left child of a node p/q is p/(p+q) and the right child is (p+q)/q.

        // We can start from the root of the tree, which is 1/1, and try to reach the target fraction targetX/targetY. We can use a loop to traverse the tree, comparing the current fraction with the target fraction at each step.

        int pL = 0, qL = 1; // Left boundary (0/1)
        int pR = 1, qR = 0; // Right boundary (1/0)

        while (true) {
            int pM = pL + pR; // Mediant numerator
            int qM = qL + qR; // Mediant denominator

            if (pM == targetX && qM == targetY) {
                return true; // Found the target fraction
            }

            if (pM * targetY < qM * targetX) {
                // Target is in the left subtree
                pR = pM;
                qR = qM;
            } else {
                // Target is in the right subtree
                pL = pM;
                qL = qM;
            }

            // If we exceed the bounds of our search, we can stop
            if (pM > targetX || qM > targetY) {
                return false; // Target cannot be reached
            }
        }           
    }
};
