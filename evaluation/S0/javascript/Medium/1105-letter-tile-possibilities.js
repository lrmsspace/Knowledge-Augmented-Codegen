// Source: https://leetcode.com/problems/letter-tile-possibilities/   |   Difficulty: Medium
//
// Problem Description:
// You have n  tiles, where each tile has one letter tiles[i] printed on it.
//
// Return the number of possible non-empty sequences of letters you can make using the letters printed on those tiles.
//
// Example:
// Input: tiles = "AAB"
// Output: 8
// Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB", "ABA", "BAA".
//
// Constraints:
// 1 <= tiles.length <= 7
// 	tiles consists of uppercase English letters.
//

/**
 * @param {string} tiles
 * @return {number}
 */
var numTilePossibilities = function(tiles) {
    const count = {};
    for (const tile of tiles) {
        count[tile] = (count[tile] || 0) + 1;
    }
    let result = 0;
    function backtrack() {
        for (const tile in count) {
            if (count[tile] === 0) continue;
            result++;
            count[tile]--;
            backtrack();
            count[tile]++;
        }
    }
    backtrack();
    return result;
        
};
