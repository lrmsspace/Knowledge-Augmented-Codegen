// Source: https://leetcode.com/problems/minimum-cost-for-cutting-cake-i/   |   Difficulty: Medium
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
// 1 <= m, n <= 20
// 	horizontalCut.length == m - 1
// 	verticalCut.length == n - 1
// 	1 <= horizontalCut[i], verticalCut[i] <= 103
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} m
 * @param {number} n
 * @param {number[]} horizontalCut
 * @param {number[]} verticalCut
 * @return {number}
 */
var minimumCost = function(m, n, horizontalCut, verticalCut) {
    horizontalCut.sort((a, b) => b - a);
    verticalCut.sort((a, b) => b - a);
    
    let totalCost = 0;
    let hIndex = 0;
    let vIndex = 0;
    let horizontalPieces = 1;
    let verticalPieces = 1;
    
    while (hIndex < horizontalCut.length && vIndex < verticalCut.length) {
        if (horizontalCut[hIndex] >= verticalCut[vIndex]) {
            totalCost += horizontalCut[hIndex] * verticalPieces;
            horizontalPieces++;
            hIndex++;
        } else {
            totalCost += verticalCut[vIndex] * horizontalPieces;
            verticalPieces++;
            vIndex++;
        }
    }
    
    while (hIndex < horizontalCut.length) {
        totalCost += horizontalCut[hIndex] * verticalPieces;
        hIndex++;
    }
    
    while (vIndex < verticalCut.length) {
        totalCost += verticalCut[vIndex] * horizontalPieces;
        vIndex++;
    }
    
    return totalCost;
};
