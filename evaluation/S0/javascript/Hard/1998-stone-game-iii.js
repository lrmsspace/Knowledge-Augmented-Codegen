// Source: https://leetcode.com/problems/stone-game-iii/   |   Difficulty: Hard
//
// Problem Description:
// Alice and Bob continue their games with piles of stones. There are several stones arranged in a row, and each stone has an associated value which is an integer given in the array stoneValue.
//
// Alice and Bob take turns, with Alice starting first. On each player's turn, that player can take 1, 2, or 3 stones from the first remaining stones in the row.
//
// The score of each player is the sum of the values of the stones taken. The score of each player is 0 initially.
//
// The objective of the game is to end with the highest score, and the winner is the player with the highest score and there could be a tie. The game continues until all the stones have been taken.
//
// Assume Alice and Bob play optimally.
//
// Return "Alice" if Alice will win, "Bob" if Bob will win, or "Tie" if they will end the game with the same score.
//
// Example:
// Input: stoneValue = [1,2,3,7]
// Output: "Bob"
// Explanation: Alice will always lose. Her best move will be to take three piles and the score become 6. Now the score of Bob is 7 and Bob wins.
//
// Constraints:
// 1 <= stoneValue.length <= 5 * 104
// 	-1000 <= stoneValue[i] <= 1000
//

/**
 * @param {number[]} stoneValue
 * @return {string}
 */
var stoneGameIII = function(stoneValue) {
    const n = stoneValue.length;
    const dp = new Array(n + 1).fill(0);
    for (let i = n - 1; i >= 0; i--) {
        let maxDiff = -Infinity;
        let currentSum = 0;
        for (let j = 0; j < 3 && i + j < n; j++) {
            currentSum += stoneValue[i + j];
            maxDiff = Math.max(maxDiff, currentSum - dp[i + j + 1]);
        }
        dp[i] = maxDiff;
    }
    if (dp[0] > 0) return "Alice";
    if (dp[0] < 0) return "Bob";
    return "Tie";
};
