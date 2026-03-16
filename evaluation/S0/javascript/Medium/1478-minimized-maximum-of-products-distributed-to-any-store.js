// Source: https://leetcode.com/problems/minimized-maximum-of-products-distributed-to-any-store/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n indicating there are n specialty retail stores. There are m product types of varying amounts, which are given as a 0-indexed integer array quantities, where quantities[i] represents the number of products of the ith product type.
//
// You need to distribute all products to the retail stores following these rules:
//
//
// 	A store can only be given at most one product type but can be given any amount of it.
// 	After distribution, each store will have been given some number of products (possibly 0). Let x represent the maximum number of products given to any store. You want x to be as small as possible, i.e., you want to minimize the maximum number of products that are given to any store.
//
//
// Return the minimum possible x.
//
// Example:
// Input: n = 6, quantities = [11,6]
// Output: 3
// Explanation: One optimal way is:
// - The 11 products of type 0 are distributed to the first four stores in these amounts: 2, 3, 3, 3
// - The 6 products of type 1 are distributed to the other two stores in these amounts: 3, 3
// The maximum number of products given to any store is max(2, 3, 3, 3, 3, 3) = 3.
//
// Constraints:
// m == quantities.length
// 	1 <= m <= n <= 105
// 	1 <= quantities[i] <= 105
//

/**
 * @param {number} n
 * @param {number[]} quantities
 * @return {number}
 */
var minimizedMaximum = function(n, quantities) {
    let left = 1;
    let right = Math.max(...quantities);

    const canDistribute = (maxProducts) => {
        let storesNeeded = 0;
        for (const quantity of quantities) {
            storesNeeded += Math.ceil(quantity / maxProducts);
            if (storesNeeded > n) {
                return false;
            }
        }
        return true;
    };

    while (left < right) {
        const mid = Math.floor((left + right) / 2);
        if (canDistribute(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;
};