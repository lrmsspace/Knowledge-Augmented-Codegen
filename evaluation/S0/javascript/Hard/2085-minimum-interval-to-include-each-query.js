// Source: https://leetcode.com/problems/minimum-interval-to-include-each-query/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array intervals, where intervals[i] = [lefti, righti] describes the ith interval starting at lefti and ending at righti (inclusive). The size of an interval is defined as the number of integers it contains, or more formally righti - lefti + 1.
//
// You are also given an integer array queries. The answer to the jth query is the size of the smallest interval i such that lefti <= queries[j] <= righti. If no such interval exists, the answer is -1.
//
// Return an array containing the answers to the queries.
//
// Example:
// Input: intervals = [[1,4],[2,4],[3,6],[4,4]], queries = [2,3,4,5]
// Output: [3,3,1,4]
// Explanation: The queries are processed as follows:
// - Query = 2: The interval [2,4] is the smallest interval containing 2. The answer is 4 - 2 + 1 = 3.
// - Query = 3: The interval [2,4] is the smallest interval containing 3. The answer is 4 - 2 + 1 = 3.
// - Query = 4: The interval [4,4] is the smallest interval containing 4. The answer is 4 - 4 + 1 = 1.
// - Query = 5: The interval [3,6] is the smallest interval containing 5. The answer is 6 - 3 + 1 = 4.
//
// Constraints:
// 1 <= intervals.length <= 105
// 	1 <= queries.length <= 105
// 	intervals[i].length == 2
// 	1 <= lefti <= righti <= 107
// 	1 <= queries[j] <= 107
//

/**
 * @param {number[][]} intervals
 * @param {number[]} queries
 * @return {number[]}
 */
var minInterval = function(intervals, queries) {
    intervals.sort((a, b) => a[0] - b[0]);
    const indexedQueries = queries.map((query, index) => [query, index]);
    indexedQueries.sort((a, b) => a[0] - b[0]);
    const result = new Array(queries.length).fill(-1);
    const minHeap = new MinPriorityQueue({ priority: x => x[0] });
    let intervalIndex = 0;
    for (const [query, queryIndex] of indexedQueries) {
        while (intervalIndex < intervals.length && intervals[intervalIndex][0] <= query) {
            const [left, right] = intervals[intervalIndex];
            minHeap.enqueue([right - left + 1, right]);
            intervalIndex++;
        }
        while (!minHeap.isEmpty() && minHeap.front().element[1] < query) {
            minHeap.dequeue();
        }
        if (!minHeap.isEmpty()) {
            result[queryIndex] = minHeap.front().element[0];
        }
    }
    return result;
};
