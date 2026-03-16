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

long long maxEnergyBoost(int* energyDrinkA, int energyDrinkASize, int* energyDrinkB, int energyDrinkBSize) {
    long long dpA[energyDrinkASize];
    long long dpB[energyDrinkBSize];

    dpA[0] = energyDrinkA[0];
    dpB[0] = energyDrinkB[0];

    for (int i = 1; i < energyDrinkASize; i++) {
        dpA[i] = energyDrinkA[i] + (i >= 2 ? fmax(dpA[i - 1], dpB[i - 2]) : dpA[i - 1]);
        dpB[i] = energyDrinkB[i] + (i >= 2 ? fmax(dpB[i - 1], dpA[i - 2]) : dpB[i - 1]);
    }

    return fmax(dpA[energyDrinkASize - 1], dpB[energyDrinkBSize - 1]);      
}
