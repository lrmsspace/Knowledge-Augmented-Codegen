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

/**
 * @param {number} n
 * @param {number[][]} languages
 * @param {number[][]} friendships
 * @return {number}
 */
var minimumTeachings = function(n, languages, friendships) {
    const m = languages.length;
    const userLanguages = Array.from({ length: m }, () => new Set());
    for (let i = 0; i < m; i++) {
        for (const lang of languages[i]) {
            userLanguages[i].add(lang);
        }
    }
    const needToTeach = new Set();
    for (const [u, v] of friendships) {
        const userU = u - 1;
        const userV = v - 1;
        let canCommunicate = false; 
        for (const lang of userLanguages[userU]) {
            if (userLanguages[userV].has(lang)) {
                canCommunicate = true;
                break;
            }
        }
        if (!canCommunicate) {
            needToTeach.add(userU);
            needToTeach.add(userV);
        }
    }
    let minTeach = Infinity;
    for (let lang = 1; lang <= n; lang++) {
        let teachCount = 0;
        for (const user of needToTeach) {
            if (!userLanguages[user].has(lang)) {
                teachCount++;
            }
        }
        minTeach = Math.min(minTeach, teachCount);
    }
    return minTeach;
};