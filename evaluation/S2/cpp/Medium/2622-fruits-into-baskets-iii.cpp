// Source: https://leetcode.com/problems/fruits-into-baskets-iii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two arrays of integers, fruits and baskets, each of length n, where fruits[i] represents the quantity of the ith type of fruit, and baskets[j] represents the capacity of the jth basket.
//
// From left to right, place the fruits according to these rules:
//
//
// 	Each fruit type must be placed in the leftmost available basket with a capacity greater than or equal to the quantity of that fruit type.
// 	Each basket can hold only one type of fruit.
// 	If a fruit type cannot be placed in any basket, it remains unplaced.
//
//
// Return the number of fruit types that remain unplaced after all possible allocations are made.
//
// Example:
// Input: fruits = [4,2,5], baskets = [3,5,4]
//
// Output: 1
//
// Explanation:
//
//
// 	fruits[0] = 4 is placed in baskets[1] = 5.
// 	fruits[1] = 2 is placed in baskets[0] = 3.
// 	fruits[2] = 5 cannot be placed in baskets[2] = 4.
//
//
// Since one fruit type remains unplaced, we return 1.
//
// Constraints:
// n == fruits.length == baskets.length
// 	1 <= n <= 105
// 	1 <= fruits[i], baskets[i] <= 109
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
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        // Sort the fruits and baskets to facilitate the allocation process
        sort(fruits.begin(), fruits.end());
        sort(baskets.begin(), baskets.end());

        int unplacedCount = 0; // Counter for unplaced fruit types
        int basketIndex = 0;   // Index to track the current basket

        // Iterate through each fruit type
        for (int fruit : fruits) {
            // Find the leftmost available basket that can accommodate the current fruit
            while (basketIndex < baskets.size() && baskets[basketIndex] < fruit) {
                basketIndex++; // Move to the next basket if the current one cannot accommodate the fruit
            }

            if (basketIndex < baskets.size()) {
                // If a suitable basket is found, move to the next basket for the next fruit
                basketIndex++;
            } else {
                // If no suitable basket is found, increment the unplaced count
                unplacedCount++;
            }
        }

        return unplacedCount; // Return the total number of unplaced fruit types            
    }
};
