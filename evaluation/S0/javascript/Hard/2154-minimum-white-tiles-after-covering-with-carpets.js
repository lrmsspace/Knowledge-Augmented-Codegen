// Source: https://leetcode.com/problems/minimum-white-tiles-after-covering-with-carpets/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed binary string floor, which represents the colors of tiles on a floor:
//
//
// 	floor[i] = '0' denotes that the ith tile of the floor is colored black.
// 	On the other hand, floor[i] = '1' denotes that the ith tile of the floor is colored white.
//
//
// You are also given numCarpets and carpetLen. You have numCarpets black carpets, each of length carpetLen tiles. Cover the tiles with the given carpets such that the number of white tiles still visible is minimum. Carpets may overlap one another.
//
// Return the minimum number of white tiles still visible.
//
// Example:
// Input: floor = "10110101", numCarpets = 2, carpetLen = 2
// Output: 2
// Explanation: 
// The figure above shows one way of covering the tiles with the carpets such that only 2 white tiles are visible.
// No other way of covering the tiles with the carpets can leave less than 2 white tiles visible.
//
// Constraints:
// 1 <= carpetLen <= floor.length <= 1000
// 	floor[i] is either '0' or '1'.
// 	1 <= numCarpets <= 1000
//

/**
 * @param {string} floor
 * @param {number} numCarpets
 * @param {number} carpetLen
 * @return {number}
 */
var minimumWhiteTiles = function(floor, numCarpets, carpetLen) {
    const n = floor.length;
    const prefixSums = new Array(n).fill(0);
    prefixSums[0] = floor[0] === '1' ? 1 : 0;
    for (let i = 1; i < n; i++) {
        prefixSums[i] = prefixSums[i - 1] + (floor[i] === '1' ? 1 : 0);
    }

    const dp = new Array(numCarpets + 1).fill(0).map(() => new Array(n).fill(Infinity));
    for (let i = 0; i <= numCarpets; i++) {
        dp[i][0] = floor[0] === '1' ? 1 : 0;
    }

    for (let i = 0; i <= numCarpets; i++) {
        for (let j = 1; j < n; j++) {
            dp[i][j] = dp[i][j - 1] + (floor[j] === '1' ? 1 : 0);
            if (i > 0) {
                const start = Math.max(0, j - carpetLen + 1);
                const covered = prefixSums[j] - (start > 0 ? prefixSums[start - 1] : 0);
                dp[i][j] = Math.min(dp[i][j], (start > 0 ? dp[i - 1][start - 1] : 0));
            }
        }
    }

    return dp[numCarpets][n - 1];
};
