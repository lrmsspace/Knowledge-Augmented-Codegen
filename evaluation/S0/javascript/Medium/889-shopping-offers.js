// Source: https://leetcode.com/problems/shopping-offers/   |   Difficulty: Medium
//
// Problem Description:
// In LeetCode Store, there are n items to sell. Each item has a price. However, there are some special offers, and a special offer consists of one or more different kinds of items with a sale price.
//
// You are given an integer array price where price[i] is the price of the ith item, and an integer array needs where needs[i] is the number of pieces of the ith item you want to buy.
//
// You are also given an array special where special[i] is of size n + 1 where special[i][j] is the number of pieces of the jth item in the ith offer and special[i][n] (i.e., the last integer in the array) is the price of the ith offer.
//
// Return the lowest price you have to pay for exactly certain items as given, where you could make optimal use of the special offers. You are not allowed to buy more items than you want, even if that would lower the overall price. You could use any of the special offers as many times as you want.
//
// Example:
// Input: price = [2,5], special = [[3,0,5],[1,2,10]], needs = [3,2]
// Output: 14
// Explanation: There are two kinds of items, A and B. Their prices are $2 and $5 respectively. 
// In special offer 1, you can pay $5 for 3A and 0B
// In special offer 2, you can pay $10 for 1A and 2B. 
// You need to buy 3A and 2B, so you may pay $10 for 1A and 2B (special offer #2), and $4 for 2A.
//
// Constraints:
// n == price.length == needs.length
// 	1 <= n <= 6
// 	0 <= price[i], needs[i] <= 10
// 	1 <= special.length <= 100
// 	special[i].length == n + 1
// 	0 <= special[i][j] <= 50
// 	The input is generated that at least one of special[i][j] is non-zero for 0 <= j <= n - 1.
//

/**
 * @param {number[]} price
 * @param {number[][]} special
 * @param {number[]} needs
 * @return {number}
 */
var shoppingOffers = function(price, special, needs) {
    const n = price.length;

    const dfs = (currentNeeds) => {
        let minCost = 0;
        for (let i = 0; i < n; i++) {
            minCost += currentNeeds[i] * price[i];
        }
        for (const offer of special) {
            const newNeeds = [];
            for (let i = 0; i < n; i++) {
                if (offer[i] > currentNeeds[i]) {
                    break;
                }
                newNeeds.push(currentNeeds[i] - offer[i]);
            }
            if (newNeeds.length === n) {
                minCost = Math.min(minCost, offer[n] + dfs(newNeeds));
            }
        }
        return minCost;
    };

    return dfs(needs);
};