// Source: https://leetcode.com/problems/maximum-total-beauty-of-the-gardens/   |   Difficulty: Hard
//
// Problem Description:
// Alice is a caretaker of n gardens and she wants to plant flowers to maximize the total beauty of all her gardens.
//
// You are given a 0-indexed integer array flowers of size n, where flowers[i] is the number of flowers already planted in the ith garden. Flowers that are already planted cannot be removed. You are then given another integer newFlowers, which is the maximum number of flowers that Alice can additionally plant. You are also given the integers target, full, and partial.
//
// A garden is considered complete if it has at least target flowers. The total beauty of the gardens is then determined as the sum of the following:
//
//
// 	The number of complete gardens multiplied by full.
// 	The minimum number of flowers in any of the incomplete gardens multiplied by partial. If there are no incomplete gardens, then this value will be 0.
//
//
// Return the maximum total beauty that Alice can obtain after planting at most newFlowers flowers.
//
// Example:
// Input: flowers = [1,3,1,1], newFlowers = 7, target = 6, full = 12, partial = 1
// Output: 14
// Explanation: Alice can plant
// - 2 flowers in the 0th garden
// - 3 flowers in the 1st garden
// - 1 flower in the 2nd garden
// - 1 flower in the 3rd garden
// The gardens will then be [3,6,2,2]. She planted a total of 2 + 3 + 1 + 1 = 7 flowers.
// There is 1 garden that is complete.
// The minimum number of flowers in the incomplete gardens is 2.
// Thus, the total beauty is 1 * 12 + 2 * 1 = 12 + 2 = 14.
// No other way of planting flowers can obtain a total beauty higher than 14.
//
// Constraints:
// 1 <= flowers.length <= 105
// 	1 <= flowers[i], target <= 105
// 	1 <= newFlowers <= 1010
// 	1 <= full, partial <= 105
//

/**
 * @param {number[]} flowers
 * @param {number} newFlowers
 * @param {number} target
 * @param {number} full
 * @param {number} partial
 * @return {number}
 */
var maximumBeauty = function(flowers, newFlowers, target, full, partial) {
    const n = flowers.length;
    const incompleteGardens = [];
    let completeCount = 0;
    for (const flower of flowers) {
        if (flower >= target) {
            completeCount += 1;
        } else {
            incompleteGardens.push(flower);
        }
    }
    incompleteGardens.sort((a, b) => a - b);
    const prefixSums = new Array(incompleteGardens.length + 1).fill(0);
    for (let i = 1; i <= incompleteGardens.length; i++) {
        prefixSums[i] = prefixSums[i - 1] + incompleteGardens[i - 1];
    }
    let maxBeauty = completeCount * full + (incompleteGardens.length > 0 ? incompleteGardens[0] * partial : 0);
    for (let i = 0; i <= incompleteGardens.length; i++) {
        const flowersNeeded = i * target - prefixSums[i];
        if (flowersNeeded > newFlowers) {
            break;
        }
        const remainingFlowers = newFlowers - flowersNeeded;
        const minIncomplete = i < incompleteGardens.length ? Math.min(incompleteGardens[i] + Math.floor(remainingFlowers / (incompleteGardens.length - i)), target - 1) : 0;
        const beauty = (completeCount + i) * full + minIncomplete * partial;
        maxBeauty = Math.max(maxBeauty, beauty);
    }
    return maxBeauty;
};
