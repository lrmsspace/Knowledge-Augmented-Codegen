// Source: https://leetcode.com/problems/determine-whether-matrix-can-be-obtained-by-rotation/   |   Difficulty: Easy
//
// Problem Description:
// Given two n x n binary matrices mat and target, return true if it is possible to make mat equal to target by rotating mat in 90-degree increments, or false otherwise.
//
// Example:
// Input: mat = [[0,1],[1,0]], target = [[1,0],[0,1]]
// Output: true
// Explanation: We can rotate mat 90 degrees clockwise to make mat equal target.
//
// Constraints:
// n == mat.length == target.length
// 	n == mat[i].length == target[i].length
// 	1 <= n <= 10
// 	mat[i][j] and target[i][j] are either 0 or 1.
//
// Helpful references (internal KB):
// - Simulated Annealing (array, number, randomized, simulation)
//   • When to use: Use when seeking a near-optimal solution for complex optimization problems with many local optima, especially when exact solutions are computationally infeasible or too slow.
//   • Idea: Simulated Annealing is a probabilistic metaheuristic for global optimization, inspired by the annealing process in metallurgy. It explores the search space by accepting worse solutions with a probability that decreases over time, aiming to escape local optima.
//   • Invariants: The `s_best` state always represents the lowest energy found across all iterations so far.; The temperature `T` is always non-negative and decreases monotonically with each iteration.
//   • Tips: Start with a sufficiently high initial temperature to allow broad exploration.; Choose a slow cooling schedule (decay rate) for better solution quality, at the cost of longer runtime.
//   • Pitfalls: Getting stuck in local minima if the cooling schedule is too fast.; Excessive runtime if the cooling schedule is too slow or initial temperature is too high.
// - Fibonacci Numbers (matrix, matrix-exp)
//   • When to use: Use when needing to compute the N-th Fibonacci number or similar linear recurrence relations for very large N efficiently, typically in logarithmic time.
//   • Idea: This method computes the N-th Fibonacci number by transforming the linear recurrence into a matrix multiplication, then using binary exponentiation (matrix exponentiation) to raise the transformation matrix to the N-th power. It achieves O(log N) time complexity.
//   • Invariants: The base matrix M = [[1, 1], [1, 0]] correctly transforms (F_k, F_{k-1}) to (F_{k+1}, F_k).; After k matrix multiplications, the accumulated matrix represents M^k.
//   • Tips: Understand binary exponentiation for matrices to efficiently compute powers.; The base transformation matrix for Fibonacci is typically [[1, 1], [1, 0]].
//   • Pitfalls: Incorrectly setting up the base matrix or initial vector.; Forgetting to apply modulo operations, leading to integer overflow for large numbers.
// - Circle-Circle Intersection (geometry, number, simulation, enumeration)
//   • When to use: Use this algorithm to find the common points where two circles intersect on a 2D plane, handling cases from no intersection to infinite points.
//   • Idea: This algorithm determines the intersection points of two circles by algebraically transforming their equations into a system involving one circle and one line. It typically achieves O(1) time complexity for finding the intersection points.
//   • Invariants: The relative positions and radii of the circles remain unchanged after coordinate translation.; The derived linear equation represents the radical axis of the two circles.
//   • Tips: Translate one circle to the origin to simplify the equations.; Subtract the two circle equations to derive a linear equation (the radical axis).
//   • Pitfalls: Numerical instability due to floating-point arithmetic, especially for tangent cases.; Forgetting to translate the resulting intersection points back to the original coordinate system.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        int n = mat.size();
        for (int rotation = 0; rotation < 4; ++rotation) {
            bool match = true;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (mat[i][j] != target[i][j]) {
                        match = false;
                        break;
                    }
                }
                if (!match) break;
            }
            if (match) return true;

            // Rotate mat 90 degrees clockwise
            vector<vector<int>> rotated(n, vector<int>(n, 0));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    rotated[j][n - 1 - i] = mat[i][j];
                }
            }
            mat = rotated;
        }
        return false;           
    }
};
