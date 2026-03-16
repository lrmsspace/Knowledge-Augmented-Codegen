// Source: https://leetcode.com/problems/the-earliest-and-latest-rounds-where-players-compete/   |   Difficulty: Hard
//
// Problem Description:
// There is a tournament where n players are participating. The players are standing in a single row and are numbered from 1 to n based on their initial standing position (player 1 is the first player in the row, player 2 is the second player in the row, etc.).
//
// The tournament consists of multiple rounds (starting from round number 1). In each round, the ith player from the front of the row competes against the ith player from the end of the row, and the winner advances to the next round. When the number of players is odd for the current round, the player in the middle automatically advances to the next round.
//
//
// 	For example, if the row consists of players 1, 2, 4, 6, 7
//
// 	
// 		Player 1 competes against player 7.
// 		Player 2 competes against player 6.
// 		Player 4 automatically advances to the next round.
// 	
// 	
//
//
// After each round is over, the winners are lined back up in the row based on the original ordering assigned to them initially (ascending order).
//
// The players numbered firstPlayer and secondPlayer are the best in the tournament. They can win against any other player before they compete against each other. If any two other players compete against each other, either of them might win, and thus you may choose the outcome of this round.
//
// Given the integers n, firstPlayer, and secondPlayer, return an integer array containing two values, the earliest possible round number and the latest possible round number in which these two players will compete against each other, respectively.
//
// Example:
// Input: n = 11, firstPlayer = 2, secondPlayer = 4
// Output: [3,4]
// Explanation:
// One possible scenario which leads to the earliest round number:
// First round: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
// Second round: 2, 3, 4, 5, 6, 11
// Third round: 2, 3, 4
// One possible scenario which leads to the latest round number:
// First round: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
// Second round: 1, 2, 3, 4, 5, 6
// Third round: 1, 2, 4
// Fourth round: 2, 4
//
// Constraints:
// 2 <= n <= 28
// 	1 <= firstPlayer < secondPlayer <= n
//

class Solution {
    public int[] earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        int earliest = Integer.MAX_VALUE;
        int latest = Integer.MIN_VALUE;

        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{n, firstPlayer, secondPlayer, 1});

        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int totalPlayers = curr[0];
            int player1 = curr[1];
            int player2 = curr[2];
            int round = curr[3];

            if (player1 + player2 == totalPlayers + 1) {
                earliest = Math.min(earliest, round);
                latest = Math.max(latest, round);
                continue;
            }

            int newTotalPlayers = (totalPlayers + 1) / 2;
            for (int i = 1; i <= totalPlayers / 2; i++) {
                int opponent1 = totalPlayers - i + 1;
                for (int j = 1; j <= totalPlayers / 2; j++) {
                    int opponent2 = totalPlayers - j + 1;

                    if ((player1 == i && player2 == opponent2) || (player1 == opponent1 && player2 == j)) {
                        continue;
                    }

                    int nextPlayer1 = getNextPosition(player1, i, opponent1, totalPlayers);
                    int nextPlayer2 = getNextPosition(player2, j, opponent2, totalPlayers);

                    queue.offer(new int[]{newTotalPlayers, nextPlayer1, nextPlayer2, round + 1});
                }
            }

            if (totalPlayers % 2 == 1) {
                int middlePlayer = (totalPlayers / 2) + 1;
                if (player1 == middlePlayer || player2 == middlePlayer) {
                    int nextPlayer1 = getNextPosition(player1, -1, -1, totalPlayers);
                    int nextPlayer2 = getNextPosition(player2, -1, -1, totalPlayers);
                    queue.offer(new int[]{newTotalPlayers, nextPlayer1, nextPlayer2, round + 1});
                }
            }
        }

        return new int[]{earliest, latest};         
    }
}
