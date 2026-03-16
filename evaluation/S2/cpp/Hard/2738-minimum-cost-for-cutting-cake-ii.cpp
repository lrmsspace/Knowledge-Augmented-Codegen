// Source: https://leetcode.com/problems/minimum-cost-for-cutting-cake-ii/   |   Difficulty: Hard
//
// Problem Description:
// There is an m x n cake that needs to be cut into 1 x 1 pieces.
//
// You are given integers m, n, and two arrays:
//
//
// 	horizontalCut of size m - 1, where horizontalCut[i] represents the cost to cut along the horizontal line i.
// 	verticalCut of size n - 1, where verticalCut[j] represents the cost to cut along the vertical line j.
//
//
// In one operation, you can choose any piece of cake that is not yet a 1 x 1 square and perform one of the following cuts:
//
//
// 	Cut along a horizontal line i at a cost of horizontalCut[i].
// 	Cut along a vertical line j at a cost of verticalCut[j].
//
//
// After the cut, the piece of cake is divided into two distinct pieces.
//
// The cost of a cut depends only on the initial cost of the line and does not change.
//
// Return the minimum total cost to cut the entire cake into 1 x 1 pieces.
//
// Example:
// Input: m = 3, n = 2, horizontalCut = [1,3], verticalCut = [5]
//
// Output: 13
//
// Explanation:
//
//
//
//
// 	Perform a cut on the vertical line 0 with cost 5, current total cost is 5.
// 	Perform a cut on the horizontal line 0 on 3 x 1 subgrid with cost 1.
// 	Perform a cut on the horizontal line 0 on 3 x 1 subgrid with cost 1.
// 	Perform a cut on the horizontal line 1 on 2 x 1 subgrid with cost 3.
// 	Perform a cut on the horizontal line 1 on 2 x 1 subgrid with cost 3.
//
//
// The total cost is 5 + 1 + 1 + 3 + 3 = 13.
//
// Constraints:
// 1 <= m, n <= 105
// 	horizontalCut.length == m - 1
// 	verticalCut.length == n - 1
// 	1 <= horizontalCut[i], verticalCut[i] <= 103
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {
        // Sort the cut costs in descending order to prioritize higher costs first
        sort(horizontalCut.rbegin(), horizontalCut.rend());
        sort(verticalCut.rbegin(), verticalCut.rend());

        long long totalCost = 0;
        int horizontalPieces = 1; // Initially, there is one horizontal piece
        int verticalPieces = 1;   // Initially, there is one vertical piece

        int i = 0, j = 0;

        // Use a greedy approach to cut the cake
        while (i < horizontalCut.size() && j < verticalCut.size()) {
            if (horizontalCut[i] >= verticalCut[j]) {
                totalCost += (long long)horizontalCut[i] * verticalPieces;
                horizontalPieces++;
                i++;
            } else {
                totalCost += (long long)verticalCut[j] * horizontalPieces;
                verticalPieces++;
                j++;
            }
        }

        // If there are remaining horizontal cuts
        while (i < horizontalCut.size()) {
            totalCost += (long long)horizontalCut[i] * verticalPieces;
            horizontalPieces++;
            i++;
        }

        // If there are remaining vertical cuts
        while (j < verticalCut.size()) {
            totalCost += (long long)verticalCut[j] * horizontalPieces;
            verticalPieces++;
            j++;
        }

        return totalCost;           
    }
};
