// Source: https://leetcode.com/problems/maximum-employees-to-be-invited-to-a-meeting/   |   Difficulty: Hard
//
// Problem Description:
// A company is organizing a meeting and has a list of n employees, waiting to be invited. They have arranged for a large circular table, capable of seating any number of employees.
//
// The employees are numbered from 0 to n - 1. Each employee has a favorite person and they will attend the meeting only if they can sit next to their favorite person at the table. The favorite person of an employee is not themself.
//
// Given a 0-indexed integer array favorite, where favorite[i] denotes the favorite person of the ith employee, return the maximum number of employees that can be invited to the meeting.
//
// Example:
// Input: favorite = [2,2,1,2]
// Output: 3
// Explanation:
// The above figure shows how the company can invite employees 0, 1, and 2, and seat them at the round table.
// All employees cannot be invited because employee 2 cannot sit beside employees 0, 1, and 3, simultaneously.
// Note that the company can also invite employees 1, 2, and 3, and give them their desired seats.
// The maximum number of employees that can be invited to the meeting is 3.
//
// Constraints:
// n == favorite.length
// 	2 <= n <= 105
// 	0 <= favorite[i] <= n - 1
// 	favorite[i] != i
//

/**
 * @param {number[]} favorite
 * @return {number}
 */
var maximumInvitations = function(favorite) {
        const n = favorite.length;  
    const visited = new Array(n).fill(false);
    const longestCycle = new Array(n).fill(0);
    const maxChain = new Array(n).fill(0);
    const dfs = (node) => {
        visited[node] = true;
        const nextNode = favorite[node];
        if (!visited[nextNode]) {
            longestCycle[node] = dfs(nextNode) + 1;
        }
        visited[node] = false;
        return longestCycle[node];
    }
    for (let i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    let maxCycleLength = 0;
    let sumOfChains = 0;
    for (let i = 0; i < n; i++) {
        const nextNode = favorite[i];
        if (favorite[nextNode] === i) {
            maxCycleLength = Math.max(maxCycleLength, longestCycle[i]);
            maxChain[i] = Math.max(maxChain[i], longestCycle[i]);
            maxChain[nextNode] = Math.max(maxChain[nextNode], longestCycle[nextNode]);
        }
    }
    for (let i = 0; i < n; i++) {
        const nextNode = favorite[i];
        if (favorite[nextNode] === i) {
            sumOfChains += maxChain[i] + maxChain[nextNode];
            maxChain[i] = 0;
            maxChain[nextNode] = 0;
        }
    }
    return Math.max(maxCycleLength, sumOfChains);   
};
