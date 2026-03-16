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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long maxEnergyBoost(vector<int>& energyDrinkA, vector<int>& energyDrinkB) {
        long long totalBoost = 0;
        int n = energyDrinkA.size();
        int currentDrink = -1; // -1: not started, 0: A, 1: B

        for (int i = 0; i < n; ++i) {
            if (currentDrink == -1) {
                // Start with the drink that gives more boost at hour i
                if (energyDrinkA[i] >= energyDrinkB[i]) {
                    totalBoost += energyDrinkA[i];
                    currentDrink = 0;
                } else {
                    totalBoost += energyDrinkB[i];
                    currentDrink = 1;
                }
            } else if (currentDrink == 0) {
                // Currently drinking A
                if (energyDrinkA[i] >= energyDrinkB[i]) {
                    totalBoost += energyDrinkA[i]; // Continue with A
                } else {
                    currentDrink = 1; // Switch to B
                    // No boost this hour due to switch
                }
            } else {
                // Currently drinking B
                if (energyDrinkB[i] >= energyDrinkA[i]) {
                    totalBoost += energyDrinkB[i]; // Continue with B
                } else {
                    currentDrink = 0; // Switch to A
                    // No boost this hour due to switch
                }
            }
        }

        return totalBoost;          
    }
};
