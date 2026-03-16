// Source: https://leetcode.com/problems/maximum-energy-boost-from-two-drinks/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays energyDrinkA and energyDrinkB of the same length n by a futuristic sports scientist. These arrays represent the energy boosts per hour provided by two different energy drinks, A and B, respectively.
//
// You want to maximize your total energy boost by drinking one energy drink per hour. However, if you want to switch from consuming one energy drink to the other, you need to wait for one hour to cleanse your system (meaning you won't get any energy boost in that hour).
//
// Return the maximum total energy boost you can gain in the next n hours.
//
// Note that you can start consuming either of the two energy drinks.
//
// Example:
// Input: energyDrinkA = [1,3,1], energyDrinkB = [3,1,1]
//
// Output: 5
//
// Explanation:
//
// To gain an energy boost of 5, drink only the energy drink A (or only B).
//
// Constraints:
// n == energyDrinkA.length == energyDrinkB.length
// 	3 <= n <= 105
// 	1 <= energyDrinkA[i], energyDrinkB[i] <= 105
//

/**
 * @param {number[]} energyDrinkA
 * @param {number[]} energyDrinkB
 * @return {number}
 */
var maxEnergyBoost = function(energyDrinkA, energyDrinkB) {
    let maxBoost = 0;
    let currentBoostA = 0;
    let currentBoostB = 0;
    for (let i = 0; i < energyDrinkA.length; i++) {
        const newBoostA = Math.max(currentBoostA + energyDrinkA[i], currentBoostB);
        const newBoostB = Math.max(currentBoostB + energyDrinkB[i], currentBoostA);
        currentBoostA = newBoostA;
        currentBoostB = newBoostB;
        maxBoost = Math.max(maxBoost, currentBoostA, currentBoostB);
    }
    return maxBoost;    
};
