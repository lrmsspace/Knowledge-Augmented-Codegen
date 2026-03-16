// Source: https://leetcode.com/problems/watering-plants-ii/   |   Difficulty: Medium
//
// Problem Description:
// Alice and Bob want to water n plants in their garden. The plants are arranged in a row and are labeled from 0 to n - 1 from left to right where the ith plant is located at x = i.
//
// Each plant needs a specific amount of water. Alice and Bob have a watering can each, initially full. They water the plants in the following way:
//
//
// 	Alice waters the plants in order from left to right, starting from the 0th plant. Bob waters the plants in order from right to left, starting from the (n - 1)th plant. They begin watering the plants simultaneously.
// 	It takes the same amount of time to water each plant regardless of how much water it needs.
// 	Alice/Bob must water the plant if they have enough in their can to fully water it. Otherwise, they first refill their can (instantaneously) then water the plant.
// 	In case both Alice and Bob reach the same plant, the one with more water currently in his/her watering can should water this plant. If they have the same amount of water, then Alice should water this plant.
//
//
// Given a 0-indexed integer array plants of n integers, where plants[i] is the amount of water the ith plant needs, and two integers capacityA and capacityB representing the capacities of Alice's and Bob's watering cans respectively, return the number of times they have to refill to water all the plants.
//
// Example:
// Input: plants = [2,2,3,3], capacityA = 5, capacityB = 5
// Output: 1
// Explanation:
// - Initially, Alice and Bob have 5 units of water each in their watering cans.
// - Alice waters plant 0, Bob waters plant 3.
// - Alice and Bob now have 3 units and 2 units of water respectively.
// - Alice has enough water for plant 1, so she waters it. Bob does not have enough water for plant 2, so he refills his can then waters it.
// So, the total number of times they have to refill to water all the plants is 0 + 0 + 1 + 0 = 1.
//
// Constraints:
// n == plants.length
// 	1 <= n <= 105
// 	1 <= plants[i] <= 106
// 	max(plants[i]) <= capacityA, capacityB <= 109
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minimumRefill(vector<int>& plants, int capacityA, int capacityB) {
        int n = plants.size();
        int i = 0, j = n - 1;
        int refillCount = 0;
        int waterA = capacityA, waterB = capacityB;

        while (i <= j) {
            if (i == j) { // Both Alice and Bob reach the same plant
                if (waterA >= plants[i] && waterB >= plants[j]) {
                    // Both can water, Alice takes precedence
                    waterA -= plants[i];
                } else if (waterA >= plants[i]) {
                    // Only Alice can water
                    waterA -= plants[i];
                } else if (waterB >= plants[j]) {
                    // Only Bob can water
                    waterB -= plants[j];
                } else {
                    // Both need to refill, Alice takes precedence
                    refillCount++;
                    waterA = capacityA - plants[i];
                }
                break; // All plants are watered
            }

            // Alice waters from the left
            if (waterA >= plants[i]) {
                waterA -= plants[i];
            } else {
                refillCount++;
                waterA = capacityA - plants[i];
            }
            i++;

            // Bob waters from the right
            if (waterB >= plants[j]) {
                waterB -= plants[j];
            } else {
                refillCount++;
                waterB = capacityB - plants[j];
            }
            j--;
        }

        return refillCount;         
    }
};
