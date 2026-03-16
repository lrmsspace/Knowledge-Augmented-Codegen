// Source: https://leetcode.com/problems/find-the-town-judge/   |   Difficulty: Easy
//
// Problem Description:
// In a town, there are n people labeled from 1 to n. There is a rumor that one of these people is secretly the town judge.
//
// If the town judge exists, then:
//
//
// 	The town judge trusts nobody.
// 	Everybody (except for the town judge) trusts the town judge.
// 	There is exactly one person that satisfies properties 1 and 2.
//
//
// You are given an array trust where trust[i] = [ai, bi] representing that the person labeled ai trusts the person labeled bi. If a trust relationship does not exist in trust array, then such a trust relationship does not exist.
//
// Return the label of the town judge if the town judge exists and can be identified, or return -1 otherwise.
//
// Example:
// Input: n = 2, trust = [[1,2]]
// Output: 2
//
// Constraints:
// 1 <= n <= 1000
// 	0 <= trust.length <= 104
// 	trust[i].length == 2
// 	All the pairs of trust are unique.
// 	ai != bi
// 	1 <= ai, bi <= n
//

/**
 * @param {number} n
 * @param {number[][]} trust
 * @return {number}
 */
var findJudge = function(n, trust) {
    const trustCounts = new Array(n + 1).fill(0);
    for (const [a, b] of trust) {
        trustCounts[a]--;
        trustCounts[b]++;
    }
    for (let i = 1; i <= n; i++) {
        if (trustCounts[i] === n - 1) {
            return i;
        }
    }
    return -1;
};