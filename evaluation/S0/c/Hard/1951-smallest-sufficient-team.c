// Source: https://leetcode.com/problems/smallest-sufficient-team/   |   Difficulty: Hard
//
// Problem Description:
// In a project, you have a list of required skills req_skills, and a list of people. The ith person people[i] contains a list of skills that the person has.
//
// Consider a sufficient team: a set of people such that for every required skill in req_skills, there is at least one person in the team who has that skill. We can represent these teams by the index of each person.
//
//
// 	For example, team = [0, 1, 3] represents the people with skills people[0], people[1], and people[3].
//
//
// Return any sufficient team of the smallest possible size, represented by the index of each person. You may return the answer in any order.
//
// It is guaranteed an answer exists.
//
// Example:
// Input: req_skills = ["java","nodejs","reactjs"], people = [["java"],["nodejs"],["nodejs","reactjs"]]
// Output: [0,2]
//
// Constraints:
// 1 <= req_skills.length <= 16
// 	1 <= req_skills[i].length <= 16
// 	req_skills[i] consists of lowercase English letters.
// 	All the strings of req_skills are unique.
// 	1 <= people.length <= 60
// 	0 <= people[i].length <= 16
// 	1 <= people[i][j].length <= 16
// 	people[i][j] consists of lowercase English letters.
// 	All the strings of people[i] are unique.
// 	Every skill in people[i] is a skill in req_skills.
// 	It is guaranteed a sufficient team exists.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* smallestSufficientTeam(char** req_skills, int req_skillsSize, char*** people, int peopleSize, int* peopleColSize, int* returnSize) {
    if (!returnSize) return NULL;

    int fullMask = (1 << req_skillsSize) - 1;
    int *dp = (int*)malloc((1 << req_skillsSize) * sizeof(int));
    int **team = (int**)malloc((1 << req_skillsSize) * sizeof(int*));
    int *teamSizes = (int*)malloc((1 << req_skillsSize) * sizeof(int));
    if (!dp || !team || !teamSizes) {
        free(dp); free(team); free(teamSizes);
        return NULL;
    }
    for (int i = 0; i <= fullMask; ++i) {
        dp[i] = peopleSize + 1; /* larger than max possible team size */
        team[i] = NULL;
        teamSizes[i] = 0;
    }
    dp[0] = 0;

    /* map skills to bits */
    int *skillMap = (int*)malloc(req_skillsSize * sizeof(int));
    if (!skillMap) {
        free(dp); free(team); free(teamSizes);
        return NULL;
    }
    for (int i = 0; i < req_skillsSize; ++i) {
        skillMap[i] = 1 << i;
    }

    for (int i = 0; i < peopleSize; ++i) {
        int personMask = 0;
        for (int j = 0; j < peopleColSize[i]; ++j) {
            for (int k = 0; k < req_skillsSize; ++k) {
                if (strcmp(people[i][j], req_skills[k]) == 0) {
                    personMask |= skillMap[k];
                    break;
                }
            }
        }
        for (int prevMask = fullMask; prevMask >= 0; --prevMask) {
            int newMask = prevMask | personMask;
            if (dp[prevMask] + 1 < dp[newMask]) {
                dp[newMask] = dp[prevMask] + 1;
                /* update team */
                free(team[newMask]);
                team[newMask] = (int*)malloc(dp[newMask] * sizeof(int));
                if (!team[newMask]) continue; /* allocation failure, skip */
                if (teamSizes[prevMask] > 0) {
                    memcpy(team[newMask], team[prevMask], teamSizes[prevMask] * sizeof(int));
                }
                team[newMask][teamSizes[prevMask]] = i;
                teamSizes[newMask] = teamSizes[prevMask] + 1;
            }
        }
    }

    int *result = team[fullMask];
    *returnSize = teamSizes[fullMask];

    free(dp);
    free(skillMap);
    free(teamSizes);
    for (int i = 0; i < fullMask; ++i) {
        if (i != fullMask) free(team[i]);
    }
    free(team);

    return result;
}