// Source: https://leetcode.com/problems/minimum-time-to-transport-all-individuals/   |   Difficulty: Hard
//
// Problem Description:
// You are given n individuals at a base camp who need to cross a river to reach a destination using a single boat. The boat can carry at most k people at a time. The trip is affected by environmental conditions that vary cyclically over m stages.
//
// Each stage j has a speed multiplier mul[j]:
//
//
// 	If mul[j] > 1, the trip slows down.
// 	If mul[j] < 1, the trip speeds up.
//
//
// Each individual i has a rowing strength represented by time[i], the time (in minutes) it takes them to cross alone in neutral conditions.
//
// Rules:
//
//
// 	A group g departing at stage j takes time equal to the maximum time[i] among its members, multiplied by mul[j] minutes to reach the destination.
// 	After the group crosses the river in time d, the stage advances by floor(d) % m steps.
// 	If individuals are left behind, one person must return with the boat. Let r be the index of the returning person, the return takes time[r] × mul[current_stage], defined as return_time, and the stage advances by floor(return_time) % m.
//
//
// Return the minimum total time required to transport all individuals. If it is not possible to transport all individuals to the destination, return -1.
//
// Example:
// Input: n = 1, k = 1, m = 2, time = [5], mul = [1.0,1.3]
//
// Output: 5.00000
//
// Explanation:
//
//
// 	Individual 0 departs from stage 0, so crossing time = 5 × 1.00 = 5.00 minutes.
// 	All team members are now at the destination. Thus, the total time taken is 5.00 minutes.
//
// Constraints:
// 1 <= n == time.length <= 12
// 	1 <= k <= 5
// 	1 <= m <= 5
// 	1 <= time[i] <= 100
// 	m == mul.length
// 	0.5 <= mul[i] <= 2.0
//

/**
 * @param {number} n
 * @param {number} k
 * @param {number} m
 * @param {number[]} time
 * @param {number[]} mul
 * @return {number}
 */
var minTime = function(n, k, m, time, mul) {
    const FULL_MASK = (1 << n) - 1;
    const dp = Array(1 << n).fill(null).map(() => Array(m).fill(Infinity));
    dp[0][0] = 0;   
    for (let mask = 0; mask <= FULL_MASK; mask++) {
        for (let stage = 0; stage < m; stage++) {
            if (dp[mask][stage] === Infinity) continue;
            const remaining = [];
            for (let i = 0; i < n; i++) {
                if (((mask >> i) & 1) === 0) {
                    remaining.push(i);
                }
            }
            const totalRemaining = remaining.length;
            if (totalRemaining === 0) continue;
            const groupCombinations = [];
            const generateCombinations = (start, currGroup) => {
                if (currGroup.length > 0 && currGroup.length <= k) {
                    groupCombinations.push([...currGroup]);
                }
                for (let i = start; i < totalRemaining; i++) {
                    currGroup.push(remaining[i]);
                    generateCombinations(i + 1, currGroup);
                    currGroup.pop();
                }
            };
            generateCombinations(0, []);
            for (const group of groupCombinations) {
                const maxTime = Math.max(...group.map(i => time[i]));
                const crossTime = maxTime * mul[stage];
                const newStage = (stage + Math.floor(crossTime)) % m;
                let newMask = mask;
                for (const i of group) {
                    newMask |= (1 << i);
                }
                if (newMask === FULL_MASK) {
                    dp[newMask][newStage] = Math.min(dp[newMask][newStage], dp[mask][stage] + crossTime);
                }
                else {
                    for (const returner of group) {
                        const returnTime = time[returner] * mul[newStage];
                        const finalStage = (newStage + Math.floor(returnTime)) % m;
                        dp[newMask ^ (1 << returner)][finalStage] = Math.min(
                            dp[newMask ^ (1 << returner)][finalStage],
                            dp[mask][stage] + crossTime + returnTime
                        );
                    }
                }
            }
        }
    }
    let result = Infinity;
    for (let stage = 0; stage < m; stage++) {
        result = Math.min(result, dp[FULL_MASK][stage]);
    }
    return result === Infinity ? -1 : result;   
};
