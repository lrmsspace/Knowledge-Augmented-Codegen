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

class Solution {
    public int findJudge(int n, int[][] trust) {
        int[] trustScores = new int[n + 1];

        for (int[] t : trust) {
            trustScores[t[0]]--; // Person a trusts someone, decrease their score
            trustScores[t[1]]++; // Person b is trusted by someone, increase their score
        }

        for (int i = 1; i <= n; i++) {
            if (trustScores[i] == n - 1) {
                return i; // Found the town judge
            }
        }

        return -1; // No town judge found           
    }
}
