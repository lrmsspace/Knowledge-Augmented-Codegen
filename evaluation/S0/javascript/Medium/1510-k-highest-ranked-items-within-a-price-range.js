// Source: https://leetcode.com/problems/k-highest-ranked-items-within-a-price-range/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed 2D integer array grid of size m x n that represents a map of the items in a shop. The integers in the grid represent the following:
//
//
// 	0 represents a wall that you cannot pass through.
// 	1 represents an empty cell that you can freely move to and from.
// 	All other positive integers represent the price of an item in that cell. You may also freely move to and from these item cells.
//
//
// It takes 1 step to travel between adjacent grid cells.
//
// You are also given integer arrays pricing and start where pricing = [low, high] and start = [row, col] indicates that you start at the position (row, col) and are interested only in items with a price in the range of [low, high] (inclusive). You are further given an integer k.
//
// You are interested in the positions of the k highest-ranked items whose prices are within the given price range. The rank is determined by the first of these criteria that is different:
//
//
// 	Distance, defined as the length of the shortest path from the start (shorter distance has a higher rank).
// 	Price (lower price has a higher rank, but it must be in the price range).
// 	The row number (smaller row number has a higher rank).
// 	The column number (smaller column number has a higher rank).
//
//
// Return the k highest-ranked items within the price range sorted by their rank (highest to lowest). If there are fewer than k reachable items within the price range, return all of them.
//
// Example:
// Input: grid = [[1,2,0,1],[1,3,0,1],[0,2,5,1]], pricing = [2,5], start = [0,0], k = 3
// Output: [[0,1],[1,1],[2,1]]
// Explanation: You start at (0,0).
// With a price range of [2,5], we can take items from (0,1), (1,1), (2,1) and (2,2).
// The ranks of these items are:
// - (0,1) with distance 1
// - (1,1) with distance 2
// - (2,1) with distance 3
// - (2,2) with distance 4
// Thus, the 3 highest ranked items in the price range are (0,1), (1,1), and (2,1).
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	0 <= grid[i][j] <= 105
// 	pricing.length == 2
// 	2 <= low <= high <= 105
// 	start.length == 2
// 	0 <= row <= m - 1
// 	0 <= col <= n - 1
// 	grid[row][col] > 0
// 	1 <= k <= m * n
//

/**
 * @param {number[][]} grid
 * @param {number[]} pricing
 * @param {number[]} start
 * @param {number} k
 * @return {number[][]}
 */
var highestRankedKItems = function(grid, pricing, start, k) {
    const m = grid.length;
    const n = grid[0].length;
    const [low, high] = pricing;
    const [startRow, startCol] = start;
    const directions = [[1,0], [-1,0], [0,1], [0,-1]];
    const visited = Array.from({ length: m }, () => new Array(n).fill(false));
    const queue = [];
    const items = [];
    queue.push([startRow, startCol, 0]);
    visited[startRow][startCol] = true;
    while (queue.length > 0) {
        const [row, col, dist] = queue.shift();
        const price = grid[row][col];
        if (price >= low && price <= high) {
            items.push([dist, price, row, col]);
        }
        for (const [dr, dc] of directions) {
            const newRow = row + dr;
            const newCol = col + dc;
            if (
                newRow >= 0 && newRow < m &&
                newCol >= 0 && newCol < n &&
                !visited[newRow][newCol] &&
                grid[newRow][newCol] !== 0
            ) {
                visited[newRow][newCol] = true;
                queue.push([newRow, newCol, dist + 1]);
            }
        }
    }
    items.sort((a, b) => {
        if (a[0] !== b[0]) return a[0] - b[0];
        if (a[1] !== b[1]) return a[1] - b[1];
        if (a[2] !== b[2]) return a[2] - b[2];
        return a[3] - b[3];
    });
    return items.slice(0, k).map(item => [item[2], item[3]]);
};