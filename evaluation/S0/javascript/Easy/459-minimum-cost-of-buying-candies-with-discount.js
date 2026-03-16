// Source: https://leetcode.com/problems/minimum-cost-of-buying-candies-with-discount/   |   Difficulty: Easy
//
// Problem Description:
// A shop is selling candies at a discount. For every two candies sold, the shop gives a third candy for free.
//
// The customer can choose any candy to take away for free as long as the cost of the chosen candy is less than or equal to the minimum cost of the two candies bought.
//
//
// 	For example, if there are 4 candies with costs 1, 2, 3, and 4, and the customer buys candies with costs 2 and 3, they can take the candy with cost 1 for free, but not the candy with cost 4.
//
//
// Given a 0-indexed integer array cost, where cost[i] denotes the cost of the ith candy, return the minimum cost of buying all the candies.
//
// Example:
// Input: cost = [1,2,3]
// Output: 5
// Explanation: We buy the candies with costs 2 and 3, and take the candy with cost 1 for free.
// The total cost of buying all candies is 2 + 3 = 5. This is the only way we can buy the candies.
// Note that we cannot buy candies with costs 1 and 3, and then take the candy with cost 2 for free.
// The cost of the free candy has to be less than or equal to the minimum cost of the purchased candies.
//
// Constraints:
// 1 <= cost.length <= 100
// 	1 <= cost[i] <= 100
//

/**
 * @param {number[]} cost
 * @return {number}
 */
var minimumCost = function(cost) {
    cost.sort((a, b) => b - a);
    let totalCost = 0;
    for (let i = 0; i < cost.length; i++) {
        if ((i + 1) % 3 !== 0) {
            totalCost += cost[i];
        }
    }
    return totalCost;
};