// Source: https://leetcode.com/problems/best-team-with-no-conflicts/   |   Difficulty: Medium
//
// Problem Description:
// You are the manager of a basketball team. For the upcoming tournament, you want to choose the team with the highest overall score. The score of the team is the sum of scores of all the players in the team.
//
// However, the basketball team is not allowed to have conflicts. A conflict exists if a younger player has a strictly higher score than an older player. A conflict does not occur between players of the same age.
//
// Given two lists, scores and ages, where each scores[i] and ages[i] represents the score and age of the ith player, respectively, return the highest overall score of all possible basketball teams.
//
// Example:
// Input: scores = [1,3,5,10,15], ages = [1,2,3,4,5]
// Output: 34
// Explanation: You can choose all the players.
//
// Constraints:
// 1 <= scores.length, ages.length <= 1000
// 	scores.length == ages.length
// 	1 <= scores[i] <= 106
// 	1 <= ages[i] <= 1000
//

int bestTeamScore(int* scores, int scoresSize, int* ages, int agesSize) {
    int players[scoresSize][2];
    for (int i = 0; i < scoresSize; i++) {
        players[i][0] = ages[i];
        players[i][1] = scores[i];
    }

    // Sort players by age, then by score
    qsort(players, scoresSize, sizeof(players[0]), [](const void* a, const void* b) {
        int ageA = ((int(*)[2])a)[0][0];
        int scoreA = ((int(*)[2])a)[0][1];
        int ageB = ((int(*)[2])b)[0][0];
        int scoreB = ((int(*)[2])b)[0][1];
        if (ageA != ageB) return ageA - ageB;
        return scoreA - scoreB;
    });

    int dp[scoresSize];
    int maxScore = 0;

    for (int i = 0; i < scoresSize; i++) {
        dp[i] = players[i][1]; // Initialize dp with the player's score
        for (int j = 0; j < i; j++) {
            if (players[i][1] >= players[j][1]) { // No conflict condition
                dp[i] = fmax(dp[i], dp[j] + players[i][1]);
            }
        }
        maxScore = fmax(maxScore, dp[i]);
    }

    return maxScore;        
}
