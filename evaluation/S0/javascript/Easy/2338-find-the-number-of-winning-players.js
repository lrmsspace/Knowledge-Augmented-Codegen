// Source: https://leetcode.com/problems/find-the-number-of-winning-players/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer n representing the number of players in a game and a 2D array pick where pick[i] = [xi, yi] represents that the player xi picked a ball of color yi.
//
// Player i wins the game if they pick strictly more than i balls of the same color. In other words,
//
//
// 	Player 0 wins if they pick any ball.
// 	Player 1 wins if they pick at least two balls of the same color.
// 	...
// 	Player i wins if they pick at least i + 1 balls of the same color.
//
//
// Return the number of players who win the game.
//
// Note that multiple players can win the game.
//
// Example:
// Input: n = 4, pick = [[0,0],[1,0],[1,0],[2,1],[2,1],[2,0]]
//
// Output: 2
//
// Explanation:
//
// Player 0 and player 1 win the game, while players 2 and 3 do not win.
//
// Constraints:
// 2 <= n <= 10
// 	1 <= pick.length <= 100
// 	pick[i].length == 2
// 	0 <= xi <= n - 1 
// 	0 <= yi <= 10
//

/**
 * @param {number} n
 * @param {number[][]} pick
 * @return {number}
 */
var winningPlayerCount = function(n, pick) {
    const colorCount = Array.from({ length: n }, () => ({}));
    for (const [player, color] of pick) {
        if (!colorCount[player][color]) {
            colorCount[player][color] = 0;
        }
        colorCount[player][color]++;
    }
    let winners = 0;
    for (let i = 0; i < n; i++) {
        for (const color in colorCount[i]) {
            if (colorCount[i][color] > i) {
                winners++;
                break;
            }
        }
    }
    return winners;
};