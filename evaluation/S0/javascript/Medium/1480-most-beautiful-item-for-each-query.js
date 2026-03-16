// Source: https://leetcode.com/problems/most-beautiful-item-for-each-query/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array items where items[i] = [pricei, beautyi] denotes the price and beauty of an item respectively.
//
// You are also given a 0-indexed integer array queries. For each queries[j], you want to determine the maximum beauty of an item whose price is less than or equal to queries[j]. If no such item exists, then the answer to this query is 0.
//
// Return an array answer of the same length as queries where answer[j] is the answer to the jth query.
//
// Example:
// Input: items = [[1,2],[3,2],[2,4],[5,6],[3,5]], queries = [1,2,3,4,5,6]
// Output: [2,4,5,5,6,6]
// Explanation:
// - For queries[0]=1, [1,2] is the only item which has price <= 1. Hence, the answer for this query is 2.
// - For queries[1]=2, the items which can be considered are [1,2] and [2,4]. 
//   The maximum beauty among them is 4.
// - For queries[2]=3 and queries[3]=4, the items which can be considered are [1,2], [3,2], [2,4], and [3,5].
//   The maximum beauty among them is 5.
// - For queries[4]=5 and queries[5]=6, all items can be considered.
//   Hence, the answer for them is the maximum beauty of all items, i.e., 6.
//
// Constraints:
// 1 <= items.length, queries.length <= 105
// 	items[i].length == 2
// 	1 <= pricei, beautyi, queries[j] <= 109
//

/**
 * @param {number[][]} items
 * @param {number[]} queries
 * @return {number[]}
 */
var maximumBeauty = function(items, queries) {
    items.sort((a, b) => a[0] - b[0]);
    const n = items.length;
    const maxBeautyUpToPrice = new Array(n);
    maxBeautyUpToPrice[0] = items[0][1];
    for (let i = 1; i < n; i++) {
        maxBeautyUpToPrice[i] = Math.max(maxBeautyUpToPrice[i - 1], items[i][1]);
    }

    const result = [];
    for (const query of queries) {
        let left = 0;
        let right = n - 1;
        let answer = 0;

        while (left <= right) {
            const mid = Math.floor((left + right) / 2);
            if (items[mid][0] <= query) {
                answer = maxBeautyUpToPrice[mid];
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        result.push(answer);
    }

    return result;
};