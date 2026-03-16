// Source: https://leetcode.com/problems/building-boxes/   |   Difficulty: Hard
//
// Problem Description:
// You have a cubic storeroom where the width, length, and height of the room are all equal to n units. You are asked to place n boxes in this room where each box is a cube of unit side length. There are however some rules to placing the boxes:
//
//
// 	You can place the boxes anywhere on the floor.
// 	If box x is placed on top of the box y, then each side of the four vertical sides of the box y must either be adjacent to another box or to a wall.
//
//
// Given an integer n, return the minimum possible number of boxes touching the floor.
//
// Example:
// Input: n = 3
// Output: 3
// Explanation: The figure above is for the placement of the three boxes.
// These boxes are placed in the corner of the room, where the corner is on the left side.
//
// Constraints:
// 1 <= n <= 109
//
// Helpful references (internal KB):
// - Lattice points inside non-lattice polygon (geometry, number, counting, recursion)
//   • When to use: Use this when you need to count integer coordinate points strictly inside a polygon whose vertices are not restricted to integer coordinates. It's suitable for problems requiring precise geometric counting with non-lattice boundaries.
//   • Idea: This algorithm counts lattice points within a polygon with arbitrary vertices by summing signed contributions from each edge. It reduces the problem to evaluating sums of floor functions, sum(floor(kx+b)), which is solved recursively, typically achieving logarithmic complexity per edge.
//   • Invariants: The sum sum(floor(kx+b)) correctly accumulates points below the current edge segment.; After coordinate transformations, the problem reduces to a sum over a non-negative range with non-negative k and b.
//   • Tips: Decompose the polygon into signed areas under each edge, similar to the shoelace formula.; Handle edge cases where k or b are negative by appropriate transformations.
//   • Pitfalls: Floating point precision issues when calculating k and b or during transformations.; Incorrectly handling boundary points (points on edges or vertices).
// - Stars and bars (number, counting)
//   • When to use: When counting the number of ways to distribute 'n' identical items into 'k' distinct containers, or finding the number of non-negative integer solutions to an equation x1 + ... + xk = n.
//   • Idea: A combinatorial technique to count arrangements of identical items into distinct bins, or non-negative integer solutions to a sum, by modeling them as permutations of 'n' stars and 'k-1' bars. It typically has a time complexity of O(1) after binomial coefficient precomputation, or O(min(n, k)) for direct calculation.
//   • Invariants: The total number of stars remains 'n' throughout the arrangement.; The total number of bars remains 'k-1' throughout the arrangement.
//   • Tips: Clearly identify 'n' (identical objects) and 'k' (distinct bins/variables).; Remember the formula: C(n + k - 1, k - 1) or C(n + k - 1, n).
//   • Pitfalls: Confusing identical objects with distinct objects.; Incorrectly identifying 'n' or 'k' in the problem statement.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minimumBoxes(int n) {
        int k = 0;
        while ((k * (k + 1) * (k + 2)) / 6 <= n) {
            k++;
        }
        k--;

        int boxesUsed = (k * (k + 1) * (k + 2)) / 6;
        int remaining = n - boxesUsed;

        int additionalLayers = 0;
        if (remaining > 0) {
            int layer = k + 1;
            while (remaining > 0) {
                additionalLayers++;
                remaining -= layer;
                layer++;
            }
        }

        int baseBoxes = (k * (k + 1)) / 2;
        int extraBoxes = (additionalLayers * (additionalLayers + 1)) / 2;

        return baseBoxes + extraBoxes;          
    }
};
