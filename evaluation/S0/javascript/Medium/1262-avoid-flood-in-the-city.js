// Source: https://leetcode.com/problems/avoid-flood-in-the-city/   |   Difficulty: Medium
//
// Problem Description:
// Your country has an infinite number of lakes. Initially, all the lakes are empty, but when it rains over the nth lake, the nth lake becomes full of water. If it rains over a lake that is full of water, there will be a flood. Your goal is to avoid floods in any lake.
//
// Given an integer array rains where:
//
//
// 	rains[i] > 0 means there will be rains over the rains[i] lake.
// 	rains[i] == 0 means there are no rains this day and you can choose one lake this day and dry it.
//
//
// Return an array ans where:
//
//
// 	ans.length == rains.length
// 	ans[i] == -1 if rains[i] > 0.
// 	ans[i] is the lake you choose to dry in the ith day if rains[i] == 0.
//
//
// If there are multiple valid answers return any of them. If it is impossible to avoid flood return an empty array.
//
// Notice that if you chose to dry a full lake, it becomes empty, but if you chose to dry an empty lake, nothing changes.
//
// Example:
// Input: rains = [1,2,3,4]
// Output: [-1,-1,-1,-1]
// Explanation: After the first day full lakes are [1]
// After the second day full lakes are [1,2]
// After the third day full lakes are [1,2,3]
// After the fourth day full lakes are [1,2,3,4]
// There's no day to dry any lake and there is no flood in any lake.
//
// Constraints:
// 1 <= rains.length <= 105
// 	0 <= rains[i] <= 109
//

/**
 * @param {number[]} rains
 * @return {number[]}
 */
var avoidFlood = function(rains) {
    
    const n = rains.length;
    const result = new Array(n).fill(1);
    const fullLakes = new Map();
    const dryDays = [];
    for (let i = 0; i < n; i++) {
        const lake = rains[i];
        if (lake > 0) {
            if (fullLakes.has(lake)) {
                const lastFullDay = fullLakes.get(lake);
                let dried = false;
                for (let j = 0; j < dryDays.length; j++) {
                    if (dryDays[j] > lastFullDay) {
                        result[dryDays[j]] = lake;
                        dryDays.splice(j, 1);
                        dried = true;
                        break;
                    }
                }
                if (!dried) {
                    return [];
                }
            }
            fullLakes.set(lake, i);
            result[i] = -1;
        }
        else {
            dryDays.push(i);
        }
    }
    return result;  
};
