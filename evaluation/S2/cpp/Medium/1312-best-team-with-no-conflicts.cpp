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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size();
        vector<pair<int, int>> players(n);
        for (int i = 0; i < n; ++i) {
            players[i] = {ages[i], scores[i]};
        }
        sort(players.begin(), players.end());

        vector<int> dp(n);
        int maxScore = 0;
        for (int i = 0; i < n; ++i) {
            dp[i] = players[i].second; // Base score is the player's own score
            for (int j = 0; j < i; ++j) {
                if (players[j].second <= players[i].second) { // No conflict
                    dp[i] = max(dp[i], dp[j] + players[i].second);
                }
            }
            maxScore = max(maxScore, dp[i]);
        }
        return maxScore;            
    }
};
