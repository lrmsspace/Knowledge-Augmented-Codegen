// Source: https://leetcode.com/problems/rank-teams-by-votes/   |   Difficulty: Medium
//
// Problem Description:
// In a special ranking system, each voter gives a rank from highest to lowest to all teams participating in the competition.
//
// The ordering of teams is decided by who received the most position-one votes. If two or more teams tie in the first position, we consider the second position to resolve the conflict, if they tie again, we continue this process until the ties are resolved. If two or more teams are still tied after considering all positions, we rank them alphabetically based on their team letter.
//
// You are given an array of strings votes which is the votes of all voters in the ranking systems. Sort all teams according to the ranking system described above.
//
// Return a string of all teams sorted by the ranking system.
//
// Example:
// Input: votes = ["ABC","ACB","ABC","ACB","ACB"]
// Output: "ACB"
// Explanation: 
// Team A was ranked first place by 5 voters. No other team was voted as first place, so team A is the first team.
// Team B was ranked second by 2 voters and ranked third by 3 voters.
// Team C was ranked second by 3 voters and ranked third by 2 voters.
// As most of the voters ranked C second, team C is the second team, and team B is the third.
//
// Constraints:
// 1 <= votes.length <= 1000
// 	1 <= votes[i].length <= 26
// 	votes[i].length == votes[j].length for 0 <= i, j < votes.length.
// 	votes[i][j] is an English uppercase letter.
// 	All characters of votes[i] are unique.
// 	All the characters that occur in votes[0] also occur in votes[j] where 1 <= j < votes.length.
//

char* rankTeams(char** votes, int votesSize) {
    int teamCount = strlen(votes[0]);
    int counts[26][26];
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            counts[i][j] = 0;
        }
    }

    for (int i = 0; i < votesSize; i++) {
        for (int j = 0; j < teamCount; j++) {
            counts[votes[i][j] - 'A'][j]++;
        }
    }

    char* teams = (char*)malloc((teamCount + 1) * sizeof(char));
    for (int i = 0; i < teamCount; i++) {
        teams[i] = votes[0][i];
    }
    teams[teamCount] = '\0';

    qsort(teams, teamCount, sizeof(char), 
        (int (*)(const void*, const void*)) (^(const char* a, const char* b) {
            for (int i = 0; i < teamCount; i++) {
                if (counts[*a - 'A'][i] != counts[*b - 'A'][i]) {
                    return counts[*b - 'A'][i] - counts[*a - 'A'][i];
                }
            }
            return *a - *b;
        })
    );

    return teams;       
}
