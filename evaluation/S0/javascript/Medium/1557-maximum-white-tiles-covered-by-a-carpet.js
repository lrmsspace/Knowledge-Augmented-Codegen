// Source: https://leetcode.com/problems/maximum-white-tiles-covered-by-a-carpet/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array tiles where tiles[i] = [li, ri] represents that every tile j in the range li <= j <= ri is colored white.
//
// You are also given an integer carpetLen, the length of a single carpet that can be placed anywhere.
//
// Return the maximum number of white tiles that can be covered by the carpet.
//
// Example:
// Input: tiles = [[1,5],[10,11],[12,18],[20,25],[30,32]], carpetLen = 10
// Output: 9
// Explanation: Place the carpet starting on tile 10. 
// It covers 9 white tiles, so we return 9.
// Note that there may be other places where the carpet covers 9 white tiles.
// It can be shown that the carpet cannot cover more than 9 white tiles.
//
// Constraints:
// 1 <= tiles.length <= 5 * 104
// 	tiles[i].length == 2
// 	1 <= li <= ri <= 109
// 	1 <= carpetLen <= 109
// 	The tiles are non-overlapping.
//

/**
 * @param {number[][]} tiles
 * @param {number} carpetLen
 * @return {number}
 */
var maximumWhiteTiles = function(tiles, carpetLen) {
    tiles.sort((a, b) => a[0] - b[0]);
    const n = tiles.length;
    const prefixSums = new Array(n + 1).fill(0);
    for (let i = 0; i < n; i++) {
        prefixSums[i + 1] = prefixSums[i] + (tiles[i][1] - tiles[i][0] + 1);
    }

    let maxCovered = 0;
    let j = 0;

    for (let i = 0; i < n; i++) {
        const start = tiles[i][0];
        const end = start + carpetLen - 1;

        while (j < n && tiles[j][1] <= end) {
            j++;
        }

        let covered = prefixSums[j] - prefixSums[i];

        if (j < n && tiles[j][0] <= end) {
            covered += end - tiles[j][0] + 1;
        }

        maxCovered = Math.max(maxCovered, covered);
    }

    return maxCovered;
};