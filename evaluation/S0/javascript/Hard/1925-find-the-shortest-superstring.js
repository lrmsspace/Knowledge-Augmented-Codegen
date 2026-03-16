// Source: https://leetcode.com/problems/find-the-shortest-superstring/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of strings words, return the smallest string that contains each string in words as a substring. If there are multiple valid strings of the smallest length, return any of them.
//
// You may assume that no string in words is a substring of another string in words.
//
// Example:
// Input: words = ["alex","loves","leetcode"]
// Output: "alexlovesleetcode"
// Explanation: All permutations of "alex","loves","leetcode" would also be accepted.
//
// Constraints:
// 1 <= words.length <= 12
// 	1 <= words[i].length <= 20
// 	words[i] consists of lowercase English letters.
// 	All the strings of words are unique.
//

/**
 * @param {string[]} words
 * @return {string}
 */
var shortestSuperstring = function(words) {
    const n = words.length;
    const overlap = Array.from({ length: n }, () => new Array(n).fill(0));
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            if (i !== j) {
                const minLength = Math.min(words[i].length, words[j].length);
                for (let k = minLength; k > 0; k--) {
                    if (words[i].endsWith(words[j].substring(0, k))) {
                        overlap[i][j] = k;
                        break;
                    }
                }
            }
        }
    }
    const dp = Array.from({ length: 1 << n }, () => new Array(n).fill(0));
    const parent = Array.from({ length: 1 << n }, () => new Array(n).fill(-1));
    for (let mask = 1; mask < (1 << n); mask++) {
        for (let j = 0; j < n; j++) {
            if ((mask & (1 << j)) > 0) {
                const prevMask = mask ^ (1 << j);
                if (prevMask === 0) continue;
                for (let i = 0; i < n; i++) {
                    if ((prevMask & (1 << i)) > 0) {
                        const val = dp[prevMask][i] + overlap[i][j];
                        if (val > dp[mask][j]) {
                            dp[mask][j] = val;
                            parent[mask][j] = i;
                        }
                    }
                }
            }
        }
    }
    let maxOverlap = -1;
    let lastIndex = -1;
    for (let i = 0; i < n; i++) {
        if (dp[(1 << n) - 1][i] > maxOverlap) {
            maxOverlap = dp[(1 << n) - 1][i];
            lastIndex = i;
        }
    }
    let mask = (1 << n) - 1;
    const path = [];
    while (lastIndex !== -1) {
        path.push(lastIndex);
        const temp = mask;
        mask ^= (1 << lastIndex);
        lastIndex = parent[temp][lastIndex];
    }
    path.reverse();
    let superstring = words[path[0]];
    for (let i = 1; i < path.length; i++) {
        const overlapLength = overlap[path[i - 1]][path[i]];
        superstring += words[path[i]].substring(overlapLength);
    }
    return superstring; 
};
