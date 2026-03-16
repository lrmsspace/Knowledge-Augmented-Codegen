// Source: https://leetcode.com/problems/maximum-elegance-of-a-k-length-subsequence/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array items of length n and an integer k.
//
// items[i] = [profiti, categoryi], where profiti and categoryi denote the profit and category of the ith item respectively.
//
// Let's define the elegance of a subsequence of items as total_profit + distinct_categories2, where total_profit is the sum of all profits in the subsequence, and distinct_categories is the number of distinct categories from all the categories in the selected subsequence.
//
// Your task is to find the maximum elegance from all subsequences of size k in items.
//
// Return an integer denoting the maximum elegance of a subsequence of items with size exactly k.
//
// Note: A subsequence of an array is a new array generated from the original array by deleting some elements (possibly none) without changing the remaining elements' relative order.
//
// Example:
// Input: items = [[3,2],[5,1],[10,1]], k = 2
// Output: 17
// Explanation: In this example, we have to select a subsequence of size 2.
// We can select items[0] = [3,2] and items[2] = [10,1].
// The total profit in this subsequence is 3 + 10 = 13, and the subsequence contains 2 distinct categories [2,1].
// Hence, the elegance is 13 + 22 = 17, and we can show that it is the maximum achievable elegance.
//
// Constraints:
// 1 <= items.length == n <= 105
// 	items[i].length == 2
// 	items[i][0] == profiti
// 	items[i][1] == categoryi
// 	1 <= profiti <= 109
// 	1 <= categoryi <= n 
// 	1 <= k <= n
//

/**
 * @param {number[][]} items
 * @param {number} k
 * @return {number}
 */
var findMaximumElegance = function(items, k) {
    items.sort((a, b) => b[0] - a[0]);
    const seen = new Set();
    const duplicates = [];
    let totalProfit = 0;
    for (let i = 0; i < k; i++) {
        totalProfit += items[i][0];
        if (seen.has(items[i][1])) {
            duplicates.push(items[i][0]);
        }
        seen.add(items[i][1]);
    }
    let elegance = totalProfit + seen.size * seen.size;
    for (let i = k; i < items.length; i++) {
        if (duplicates.length === 0) {
            break;
        }
        if (!seen.has(items[i][1])) {
            totalProfit += items[i][0] - duplicates.pop();
            seen.add(items[i][1]);
            elegance = Math.max(elegance, totalProfit + seen.size * seen.size);
        }
    }
    return elegance;
};
