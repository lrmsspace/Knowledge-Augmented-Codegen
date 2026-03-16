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
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (matrix, array, dp-2d, counting)
//   • When to use: Use when needing to count elements satisfying "at least one" of several properties, especially when direct counting is complicated by overlapping sets. It's also applicable for counting elements satisfying "none" of the properties by subtracting from the total.
//   • Idea: The Inclusion-Exclusion Principle is a combinatorial method to determine the size of the union of multiple finite sets. It works by summing the sizes of individual sets, subtracting the sizes of all pairwise intersections, adding back the sizes of all three-way intersections, and so on, with alternating signs.
//   • Invariants: The count for any element satisfying `k` properties is adjusted to be exactly 1 in the final sum.; Each term in the sum corresponds to the size of an intersection of a distinct subset of properties.
//   • Tips: Clearly define the universe and the properties (sets) you are interested in.; Systematically list all combinations of properties for intersection terms.
//   • Pitfalls: Incorrectly identifying or defining the properties or sets.; Missing certain intersection terms or double-counting them.
// - Placing Bishops on a Chessboard (array, counting, dp-2d)
//   • When to use: Use when counting non-attacking piece placements on a grid, especially when the problem can be decomposed into independent subproblems based on board properties like diagonals.
//   • Idea: This algorithm employs 2D dynamic programming to count the total number of ways to place non-attacking bishops on a chessboard. It leverages the independence of placements on black and white squares/diagonals, achieving a polynomial time complexity.
//   • Invariants: For any diagonal `i`, `D[i][j]` represents the number of ways to place `j` bishops on diagonal `i`.; Bishops placed on black diagonals do not attack bishops placed on white diagonals.
//   • Tips: Decompose the problem into independent subproblems for black and white squares/diagonals.; Identify the state for DP, typically `dp[diagonal_index][bishops_placed]`.
//   • Pitfalls: Incorrectly calculating the number of squares on each diagonal.; Overlapping bishops if diagonal definitions are not precise.
// - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
//   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
//   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
//   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
//   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
//   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number[][]} pick
 * @return {number}
 */
var winningPlayerCount = function(n, pick) {
    const colorCount = Array.from({ length: n }, () => new Map()); // Create an array of maps to count the number of balls of each color picked by each player
    for (const [player, color] of pick) { // Iterate through each pick and populate the color count for each player
        if (!colorCount[player].has(color)) {
            colorCount[player].set(color, 0); // Initialize the count for this color if it doesn't exist
        }
        colorCount[player].set(color, colorCount[player].get(color) + 1); // Increment the count of this color for the player
    }
    let winningPlayers = 0;
    for (let player = 0; player < n; player++) {
        for (const count of colorCount[player].values()) {
            if (count > player) {
                winningPlayers++;
                break;
            }
        }
    }
    return winningPlayers;
};
