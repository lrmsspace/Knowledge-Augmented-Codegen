// Source: https://leetcode.com/problems/number-of-paths-with-max-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given a square board of characters. You can move on the board starting at the bottom right square marked with the character 'S'.
//
// You need to reach the top left square marked with the character 'E'. The rest of the squares are labeled either with a numeric character 1, 2, ..., 9 or with an obstacle 'X'. In one move you can go up, left or up-left (diagonally) only if there is no obstacle there.
//
// Return a list of two integers: the first integer is the maximum sum of numeric characters you can collect, and the second is the number of such paths that you can take to get that maximum sum, taken modulo 10^9 + 7.
//
// In case there is no path, return [0, 0].
//
// Example:
// Input: board = ["E23","2X2","12S"]
// Output: [7,1]
//
// Constraints:
// 2 <= board.length == board[i].length <= 100
//

/**
 * @param {string[]} board
 * @return {number[]}
 */
var pathsWithMaxScore = function(board) {
    const m = board.length;
    const n = board[0].length;
    const dp = Array.from({ length: m }, () => new Array(n).fill(null));
    dp[m - 1][n - 1] = [0, 1];
    for (let i = m - 1; i >= 0; i--) {
        for (let j = n - 1; j >= 0; j--) {
            if (board[i][j] === 'X' || (i === m - 1 && j === n - 1)) {
                continue;
            }
            let maxScore = -1;
            let pathCount = 0;
            for (const [dx, dy] of [[-1, 0], [0, -1], [-1, -1]]) {
                const x = i + dx;
                const y = j + dy;
                if (x >= 0 && y >= 0 && dp[x][y] !== null) {
                    const [score, count] = dp[x][y];
                    if (score > maxScore) {
                        maxScore = score;
                        pathCount = count;
                    }
                    else if (score === maxScore) {
                        pathCount = (pathCount + count) % 1000000007;
                    }
                }
            }
            if (maxScore >= 0) {
                dp[i][j] = [maxScore + (board[i][j] >= '1' && board[i][j] <= '9' ? parseInt(board[i][j]) : 0), pathCount];
            }
        }
    }
    return dp[0][0] === null ? [0, 0] : dp[0][0];   
};
