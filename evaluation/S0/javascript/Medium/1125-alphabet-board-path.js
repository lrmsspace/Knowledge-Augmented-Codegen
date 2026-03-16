// Source: https://leetcode.com/problems/alphabet-board-path/   |   Difficulty: Medium
//
// Problem Description:
// On an alphabet board, we start at position (0, 0), corresponding to character board[0][0].
//
// Here, board = ["abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"], as shown in the diagram below.
//
//
//
// We may make the following moves:
//
//
// 	'U' moves our position up one row, if the position exists on the board;
// 	'D' moves our position down one row, if the position exists on the board;
// 	'L' moves our position left one column, if the position exists on the board;
// 	'R' moves our position right one column, if the position exists on the board;
// 	'!' adds the character board[r][c] at our current position (r, c) to the answer.
//
//
// (Here, the only positions that exist on the board are positions with letters on them.)
//
// Return a sequence of moves that makes our answer equal to target in the minimum number of moves.  You may return any path that does so.
//
// Example:
// Input: target = "leet"
// Output: "DDR!UURRR!!DDD!"
//
// Constraints:
// 1 <= target.length <= 100
// 	target consists only of English lowercase letters.
//

/**
 * @param {string} target
 * @return {string}
 */
var alphabetBoardPath = function(target) {
    const board = {};
    for (let i = 0; i < 26; i++) {
        const char = String.fromCharCode(97 + i);
        board[char] = [Math.floor(i / 5), i % 5];
    }
    let result = '';
    let currentPos = [0, 0];
    for (const char of target) {
        const targetPos = board[char];
        const rowDiff = targetPos[0] - currentPos[0];
        const colDiff = targetPos[1] - currentPos[1];
        // Special handling for 'z' to avoid invalid moves
        if (char === 'z') {
            if (colDiff < 0) result += 'L'.repeat(-colDiff);
            if (rowDiff > 0) result += 'D'.repeat(rowDiff);
            if (colDiff > 0) result += 'R'.repeat(colDiff);
            if (rowDiff < 0) result += 'U'.repeat(-rowDiff);
        } else {
            if (rowDiff < 0) result += 'U'.repeat(-rowDiff);
            if (colDiff < 0) result += 'L'.repeat(-colDiff);
            if (rowDiff > 0) result += 'D'.repeat(rowDiff);
            if (colDiff > 0) result += 'R'.repeat(colDiff);
        }
        result += '!';
        currentPos = targetPos;
    }
    return result;
        
};
