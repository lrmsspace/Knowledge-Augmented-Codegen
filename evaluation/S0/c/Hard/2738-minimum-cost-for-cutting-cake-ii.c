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

long long minimumCost(int m, int n, int* horizontalCut, int horizontalCutSize, int* verticalCut, int verticalCutSize) {
    qsort(horizontalCut, horizontalCutSize, sizeof(int), cmpInt);
    qsort(verticalCut, verticalCutSize, sizeof(int), cmpInt);

    long long totalCost = 0;
    int hPieces = 1, vPieces = 1;
    int hi = horizontalCutSize - 1, vi = verticalCutSize - 1;

    while (hi >= 0 || vi >= 0) {
        if (hi >= 0 && (vi < 0 || horizontalCut[hi] >= verticalCut[vi])) {
            totalCost += (long long)horizontalCut[hi] * vPieces;
            hPieces++;
            hi--;
        } else {
            totalCost += (long long)verticalCut[vi] * hPieces;
            vPieces++;
            vi--;
        }
    }

    return totalCost;       
}
