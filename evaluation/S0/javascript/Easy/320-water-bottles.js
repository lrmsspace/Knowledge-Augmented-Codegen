// Source: https://leetcode.com/problems/water-bottles/   |   Difficulty: Easy
//
// Problem Description:
// There are numBottles water bottles that are initially full of water. You can exchange numExchange empty water bottles from the market with one full water bottle.
//
// The operation of drinking a full water bottle turns it into an empty bottle.
//
// Given the two integers numBottles and numExchange, return the maximum number of water bottles you can drink.
//
// Example:
// Input: numBottles = 9, numExchange = 3
// Output: 13
// Explanation: You can exchange 3 empty bottles to get 1 full water bottle.
// Number of water bottles you can drink: 9 + 3 + 1 = 13.
//
// Constraints:
// 1 <= numBottles <= 100
// 	2 <= numExchange <= 100
//

/**
 * @param {number} numBottles
 * @param {number} numExchange
 * @return {number}
 */
var numWaterBottles = function(numBottles, numExchange) {
    let totalDrunk = numBottles;
    let emptyBottles = numBottles;
    while (emptyBottles >= numExchange) {
        const newBottles = Math.floor(emptyBottles / numExchange);
        totalDrunk += newBottles;
        emptyBottles = newBottles + (emptyBottles % numExchange);
    }
    return totalDrunk;
};