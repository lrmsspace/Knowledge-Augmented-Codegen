// Source: https://leetcode.com/problems/fruits-into-baskets-ii/   |   Difficulty: Easy
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
// 	1 <= n <= 100
// 	1 <= fruits[i], baskets[i] <= 1000
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} fruits
 * @param {number[]} baskets
 * @return {number}
 */
var numOfUnplacedFruits = function(fruits, baskets) {
    let unplacedCount = 0;
    const usedBaskets = new Set();
    
    for (const fruit of fruits) {
        let placed = false;
        
        for (let i = 0; i < baskets.length; i++) {
            if (!usedBaskets.has(i) && baskets[i] >= fruit) {
                usedBaskets.add(i); // Mark this basket as used
                placed = true;
                break;
            }
        }
        
        if (!placed) {
            unplacedCount++;
        }
    }
    
    return unplacedCount;
};
