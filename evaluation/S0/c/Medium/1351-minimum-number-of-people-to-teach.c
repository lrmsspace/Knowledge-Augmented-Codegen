// Source: https://leetcode.com/problems/minimum-number-of-people-to-teach/   |   Difficulty: Medium
//
// Problem Description:
// On a social network consisting of m users and some friendships between users, two users can communicate with each other if they know a common language.
//
// You are given an integer n, an array languages, and an array friendships where:
//
//
// 	There are n languages numbered 1 through n,
// 	languages[i] is the set of languages the i​​​​​​th​​​​ user knows, and
// 	friendships[i] = [u​​​​​​i​​​, v​​​​​​i] denotes a friendship between the users u​​​​​​​​​​​i​​​​​ and vi.
//
//
// You can choose one language and teach it to some users so that all friends can communicate with each other. Return the minimum number of users you need to teach.
// Note that friendships are not transitive, meaning if x is a friend of y and y is a friend of z, this doesn't guarantee that x is a friend of z.
//
// Example:
// Input: n = 2, languages = [[1],[2],[1,2]], friendships = [[1,2],[1,3],[2,3]]
// Output: 1
// Explanation: You can either teach user 1 the second language or user 2 the first language.
//
// Constraints:
// 2 <= n <= 500
// 	languages.length == m
// 	1 <= m <= 500
// 	1 <= languages[i].length <= n
// 	1 <= languages[i][j] <= n
// 	1 <= u​​​​​​i < v​​​​​​i <= languages.length
// 	1 <= friendships.length <= 500
// 	All tuples (u​​​​​i, v​​​​​​i) are unique
// 	languages[i] contains only unique values
//

int minimumTeachings(int n, int** languages, int languagesSize, int* languagesColSize, int** friendships, int friendshipsSize, int* friendshipsColSize) {
    int i, j, k;
    int cannotCommunicateCount = 0;
    int languageCount[501] = {0};
    int cannotCommunicateUsers[501] = {0};

    // Identify users who cannot communicate with their friends
    for (i = 0; i < friendshipsSize; i++) {
        int u = friendships[i][0] - 1;
        int v = friendships[i][1] - 1;
        int canCommunicate = 0;

        for (j = 0; j < languagesColSize[u]; j++) {
            for (k = 0; k < languagesColSize[v]; k++) {
                if (languages[u][j] == languages[v][k]) {
                    canCommunicate = 1;
                    break;
                }
            }
            if (canCommunicate) break;
        }

        if (!canCommunicate) {
            cannotCommunicateCount++;
            cannotCommunicateUsers[u] = 1;
            cannotCommunicateUsers[v] = 1;
        }
    }

    // Count how many users need to learn each language
    for (i = 0; i < languagesSize; i++) {
        if (cannotCommunicateUsers[i]) {
            for (j = 0; j < languagesColSize[i]; j++) {
                languageCount[languages[i][j]]++;
            }
        }
    }

    // Find the language that requires the minimum number of teachings
    int maxKnown = 0;
    for (i = 1; i <= n; i++) {
        if (languageCount[i] > maxKnown) {
            maxKnown = languageCount[i];
        }
    }

    return cannotCommunicateCount - maxKnown;       
}
