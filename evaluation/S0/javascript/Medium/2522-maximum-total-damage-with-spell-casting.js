// Source: https://leetcode.com/problems/maximum-total-damage-with-spell-casting/   |   Difficulty: Medium
//
// Problem Description:
// A magician has various spells.
//
// You are given an array power, where each element represents the damage of a spell. Multiple spells can have the same damage value.
//
// It is a known fact that if a magician decides to cast a spell with a damage of power[i], they cannot cast any spell with a damage of power[i] - 2, power[i] - 1, power[i] + 1, or power[i] + 2.
//
// Each spell can be cast only once.
//
// Return the maximum possible total damage that a magician can cast.
//
// Example:
// Input: power = [1,1,3,4]
//
// Output: 6
//
// Explanation:
//
// The maximum possible damage of 6 is produced by casting spells 0, 1, 3 with damage 1, 1, 4.
//
// Constraints:
// 1 <= power.length <= 105
// 	1 <= power[i] <= 109
//

/**
 * @param {number[]} power
 * @return {number}
 */
var maximumTotalDamage = function(power) {
    const damageCount = new Map();
    for (const p of power) {
        damageCount.set(p, (damageCount.get(p) || 0) + 1);
    }
    const uniquePowers = Array.from(damageCount.keys()).sort((a, b) => a - b);
    const n = uniquePowers.length;
    const dp = new Array(n).fill(0);
    for (let i = 0; i < n; i++) {
        const currentPower = uniquePowers[i];
        const currentDamage = currentPower * damageCount.get(currentPower);
        if (i === 0) {
            dp[i] = currentDamage;
        } else if (i === 1) {
            if (uniquePowers[1] - uniquePowers[0] <= 2) {
                dp[i] = Math.max(dp[0], currentDamage);
            } else {
                dp[i] = dp[0] + currentDamage;
            }
        } else {
            if (uniquePowers[i] - uniquePowers[i - 1] <= 2) {
                dp[i] = Math.max(dp[i - 1], dp[i - 2] + currentDamage);
            } else {
                dp[i] = dp[i - 1] + currentDamage;
            }
        }
    }
    return dp[n - 1];
};