// Source: https://leetcode.com/problems/divide-players-into-teams-of-equal-skill/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer array skill of even length n where skill[i] denotes the skill of the ith player. Divide the players into n / 2 teams of size 2 such that the total skill of each team is equal.
//
// The chemistry of a team is equal to the product of the skills of the players on that team.
//
// Return the sum of the chemistry of all the teams, or return -1 if there is no way to divide the players into teams such that the total skill of each team is equal.
//
// Example:
// Input: skill = [3,2,5,1,3,4]
// Output: 22
// Explanation: 
// Divide the players into the following teams: (1, 5), (2, 4), (3, 3), where each team has a total skill of 6.
// The sum of the chemistry of all the teams is: 1 * 5 + 2 * 4 + 3 * 3 = 5 + 8 + 9 = 22.
//
// Constraints:
// 2 <= skill.length <= 105
// 	skill.length is even.
// 	1 <= skill[i] <= 1000
//

/**
 * @param {number[]} skill
 * @return {number}
 */
var dividePlayers = function(skill) {
    const n = skill.length;
    skill.sort((a, b) => a - b);
    const targetSum = skill[0] + skill[n - 1];
    let totalChemistry = 0;
    for (let i = 0; i < n / 2; i++) {
        if (skill[i] + skill[n - 1 - i] !== targetSum) {
            return -1;
        }
        totalChemistry += skill[i] * skill[n - 1 - i];
    }
    return totalChemistry;
};