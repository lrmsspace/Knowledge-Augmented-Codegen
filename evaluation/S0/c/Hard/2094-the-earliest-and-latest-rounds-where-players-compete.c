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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* earliestAndLatest(int n, int firstPlayer, int secondPlayer, int* returnSize) {
    if (!returnSize) return NULL;

    int maxRounds = 0;
    int temp = n;
    while (temp > 1) {
        maxRounds++;
        temp = (temp + 1) / 2;
    }

    int dpEarliest[29][29][29] = {{{0}}};
    int dpLatest[29][29][29] = {{{0}}};

    for (int round = 1; round <= maxRounds; round++) {
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (i + j == n + 1 || i + j == n + 2) {
                    dpEarliest[round][i][j] = 1;
                    dpLatest[round][i][j] = 1;
                } else {
                    int earliest = maxRounds + 1;
                    int latest = 0;
                    int totalPlayers = (n + (1 << (round - 1)) - 1) / (1 << (round - 1));
                    for (int k = 1; k <= totalPlayers / 2; k++) {
                        int leftPlayer = k;
                        int rightPlayer = totalPlayers - k + 1;

                        int newI = (i < leftPlayer) ? i : (i > rightPlayer) ? i - 2 * k + 1 : -1;
                        int newJ = (j < leftPlayer) ? j : (j > rightPlayer) ? j - 2 * k + 1 : -1;

                        if (newI != -1 && newJ != -1 && newI < newJ) {
                            if (dpEarliest[round - 1][newI][newJ]) {
                                earliest = (earliest < dpEarliest[round - 1][newI][newJ] + 1) ? earliest : dpEarliest[round - 1][newI][newJ] + 1;
                                latest = (latest > dpLatest[round - 1][newI][newJ] + 1) ? latest : dpLatest[round - 1][newI][newJ] + 1;
                            }
                        }
                    }
                    if (earliest != maxRounds + 1) {        
                        dpEarliest[round][i][j] = earliest;
                        dpLatest[round][i][j] = latest;
                    }
                    
                }
            }
        }
    }

    *returnSize = 2;
    int *result = (int *)malloc(2 * sizeof(int));
    result[0] = dpEarliest[maxRounds][firstPlayer][secondPlayer];
    result[1] = dpLatest[maxRounds][firstPlayer][secondPlayer];
    return result;
}