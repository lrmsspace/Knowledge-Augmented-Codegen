// Source: https://leetcode.com/problems/find-players-with-zero-or-one-losses/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array matches where matches[i] = [winneri, loseri] indicates that the player winneri defeated player loseri in a match.
//
// Return a list answer of size 2 where:
//
//
// 	answer[0] is a list of all players that have not lost any matches.
// 	answer[1] is a list of all players that have lost exactly one match.
//
//
// The values in the two lists should be returned in increasing order.
//
// Note:
//
//
// 	You should only consider the players that have played at least one match.
// 	The testcases will be generated such that no two matches will have the same outcome.
//
// Example:
// Input: matches = [[1,3],[2,3],[3,6],[5,6],[5,7],[4,5],[4,8],[4,9],[10,4],[10,9]]
// Output: [[1,2,10],[4,5,7,8]]
// Explanation:
// Players 1, 2, and 10 have not lost any matches.
// Players 4, 5, 7, and 8 each have lost one match.
// Players 3, 6, and 9 each have lost two matches.
// Thus, answer[0] = [1,2,10] and answer[1] = [4,5,7,8].
//
// Constraints:
// 1 <= matches.length <= 105
// 	matches[i].length == 2
// 	1 <= winneri, loseri <= 105
// 	winneri != loseri
// 	All matches[i] are unique.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findWinners(int** matches, int matchesSize, int* matchesColSize, int* returnSize, int** returnColumnSizes) {
    int lossCount[100001] = {0};
    int playerExists[100001] = {0};
    for (int i = 0; i < matchesSize; i++) {
        int winner = matches[i][0];
        int loser = matches[i][1];
        playerExists[winner] = 1;
        playerExists[loser] = 1;
        lossCount[loser]++;
    }

    int** result = (int**)malloc(2 * sizeof(int*));
    result[0] = (int*)malloc(100001 * sizeof(int));
    result[1] = (int*)malloc(100001 * sizeof(int));
    (*returnColumnSizes) = (int*)malloc(2 * sizeof(int));
    (*returnColumnSizes)[0] = 0;
    (*returnColumnSizes)[1] = 0;

    for (int player = 1; player <= 100000; player++) {
        if (playerExists[player]) {
            if (lossCount[player] == 0) {
                result[0][(*returnColumnSizes)[0]++] = player;
            } else if (lossCount[player] == 1) {
                result[1][(*returnColumnSizes)[1]++] = player;
            }
        }
    }

    *returnSize = 2;
    return result;      
}
