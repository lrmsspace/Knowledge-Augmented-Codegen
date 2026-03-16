// Source: https://leetcode.com/problems/maximum-number-of-groups-getting-fresh-donuts/   |   Difficulty: Hard
//
// Problem Description:
// There is a donuts shop that bakes donuts in batches of batchSize. They have a rule where they must serve all of the donuts of a batch before serving any donuts of the next batch. You are given an integer batchSize and an integer array groups, where groups[i] denotes that there is a group of groups[i] customers that will visit the shop. Each customer will get exactly one donut.
//
// When a group visits the shop, all customers of the group must be served before serving any of the following groups. A group will be happy if they all get fresh donuts. That is, the first customer of the group does not receive a donut that was left over from the previous group.
//
// You can freely rearrange the ordering of the groups. Return the maximum possible number of happy groups after rearranging the groups.
//
// Example:
// Input: batchSize = 3, groups = [1,2,3,4,5,6]
// Output: 4
// Explanation: You can arrange the groups as [6,2,4,5,1,3]. Then the 1st, 2nd, 4th, and 6th groups will be happy.
//
// Constraints:
// 1 <= batchSize <= 9
// 	1 <= groups.length <= 30
// 	1 <= groups[i] <= 109
//

/**
 * @param {number} batchSize
 * @param {number[]} groups
 * @return {number}
 */
var maxHappyGroups = function(batchSize, groups) {
    const count = new Array(batchSize).fill(0);
    for (const group of groups) {
        count[group % batchSize]++;
    }
    let happyGroups = count[0];
    const remainderGroups = [];
    for (let i = 1; i < batchSize; i++) {
        if (count[i] > 0) {
            remainderGroups.push(count[i]);
        }
    }
    const memo = new Map();
    const dfs = (state, currentRemainder) => {
        if (memo.has(state)) {
            return memo.get(state);
        }
        let maxHappy = 0;
        for (let i = 0; i < remainderGroups.length; i++) {
            if (remainderGroups[i] > 0) {
                remainderGroups[i]--;
                const newRemainder = (currentRemainder + i) % batchSize;
                maxHappy = Math.max(maxHappy, (newRemainder === 0 ? 1 : 0) + dfs(state - (1 << i), newRemainder));
                remainderGroups[i]++;
            }
        }
        memo.set(state, maxHappy);
        return maxHappy;
    }
    return happyGroups + dfs((1 << remainderGroups.length) - 1, 0); 
};
