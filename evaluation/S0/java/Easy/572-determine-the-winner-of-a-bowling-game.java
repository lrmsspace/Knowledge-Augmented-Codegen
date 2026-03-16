// Source: https://leetcode.com/problems/determine-the-winner-of-a-bowling-game/   |   Difficulty: Easy
//
// Problem Description:
// You are given two 0-indexed integer arrays player1 and player2, representing the number of pins that player 1 and player 2 hit in a bowling game, respectively.
//
// The bowling game consists of n turns, and the number of pins in each turn is exactly 10.
//
// Assume a player hits xi pins in the ith turn. The value of the ith turn for the player is:
//
//
// 	2xi if the player hits 10 pins in either (i - 1)th or (i - 2)th turn.
// 	Otherwise, it is xi.
//
//
// The score of the player is the sum of the values of their n turns.
//
// Return
//
//
// 	1 if the score of player 1 is more than the score of player 2,
// 	2 if the score of player 2 is more than the score of player 1, and
// 	0 in case of a draw.
//
// Example:
// Input: player1 = [5,10,3,2], player2 = [6,5,7,3]
//
// Output: 1
//
// Explanation:
//
// The score of player 1 is 5 + 10 + 2*3 + 2*2 = 25.
//
// The score of player 2 is 6 + 5 + 7 + 3 = 21.
//
// Constraints:
// n == player1.length == player2.length
// 	1 <= n <= 1000
// 	0 <= player1[i], player2[i] <= 10
//

class Solution {
    public int isWinner(int[] player1, int[] player2) {
        int score1 = calculateScore(player1);
        int score2 = calculateScore(player2);

        if (score1 > score2) {
            return 1;
        } else if (score2 > score1) {
            return 2;
        } else {
            return 0;
        }           
    }
}
