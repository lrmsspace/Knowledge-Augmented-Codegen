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

class Solution {
public:
    int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {
        int m = languages.size();
        vector<unordered_set<int>> userLanguages(m);
        for (int i = 0; i < m; ++i) {
            for (int lang : languages[i]) {
                userLanguages[i].insert(lang);
            }
        }

        unordered_set<int> toTeach;
        for (const auto& friendship : friendships) {
            int u = friendship[0] - 1;
            int v = friendship[1] - 1;
            bool canCommunicate = false;
            for (int lang : userLanguages[u]) {
                if (userLanguages[v].count(lang)) {
                    canCommunicate = true;
                    break;
                }
            }
            if (!canCommunicate) {
                toTeach.insert(u);
                toTeach.insert(v);
            }
        }

        vector<int> languageCount(n + 1, 0);
        for (int user : toTeach) {
            for (int lang = 1; lang <= n; ++lang) {
                if (!userLanguages[user].count(lang)) {
                    languageCount[lang]++;
                }
            }
        }

        int minToTeach = INT_MAX;
        for (int lang = 1; lang <= n; ++lang) {
            minToTeach = min(minToTeach, languageCount[lang]);
        }

        return minToTeach == INT_MAX ? 0 : minToTeach;          
    }
};
