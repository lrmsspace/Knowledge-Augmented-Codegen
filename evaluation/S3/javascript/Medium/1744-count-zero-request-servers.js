// Source: https://leetcode.com/problems/count-zero-request-servers/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n denoting the total number of servers and a 2D 0-indexed integer array logs, where logs[i] = [server_id, time] denotes that the server with id server_id received a request at time time.
//
// You are also given an integer x and a 0-indexed integer array queries.
//
// Return a 0-indexed integer array arr of length queries.length where arr[i] represents the number of servers that did not receive any requests during the time interval [queries[i] - x, queries[i]].
//
// Note that the time intervals are inclusive.
//
// Example:
// Input: n = 3, logs = [[1,3],[2,6],[1,5]], x = 5, queries = [10,11]
// Output: [1,2]
// Explanation: 
// For queries[0]: The servers with ids 1 and 2 get requests in the duration of [5, 10]. Hence, only server 3 gets zero requests.
// For queries[1]: Only the server with id 2 gets a request in duration of [6,11]. Hence, the servers with ids 1 and 3 are the only servers that do not receive any requests during that time period.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= logs.length <= 105
// 	1 <= queries.length <= 105
// 	logs[i].length == 2
// 	1 <= logs[i][0] <= n
// 	1 <= logs[i][1] <= 106
// 	1 <= x <= 105
// 	x < queries[i] <= 106
//
// Helpful references (internal KB):
// - Range Minimum Query (array, sparse-table)
//   • When to use: When performing many range minimum queries on a static array, especially when query time needs to be logarithmic after initial preprocessing.
//   • Idea: A data structure that precomputes minimums for all possible ranges of power-of-two lengths, allowing O(1) query time after O(N log N) preprocessing. It efficiently answers range minimum queries on an immutable array.
//   • Invariants: For any `j`, `dp[i][j]` stores the minimum value in the segment starting at `i` with length `2^j`.; The `log_table[k]` stores `floor(log2(k))` for efficient length calculation.
//   • Tips: Precompute log values or use `std::log2` for efficient length calculations.; The `dp[i][j]` entry stores the minimum in the range `[i, i + 2^j - 1]`.
//   • Pitfalls: Does not support updates to the array elements; it's for static data only.; Higher memory consumption compared to some other range query structures.
// - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
//   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
//   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
//   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
//   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
//   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
// - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
//   • When to use: Use when you need to perform O(1) range queries on a static array for an associative operation, after an O(N log N) preprocessing step.
//   • Idea: A data structure that precomputes answers for all possible range queries using an associative operation on a static array. It achieves O(1) query time and O(N log N) build time by storing prefix-like sums within logarithmically sized blocks.
//   • Invariants: For each level k, the array is partitioned into 2^k segments.; Within each segment, table[k][j] stores the result of the associative operation from j to the segment's midpoint (or midpoint to j).
//   • Tips: Ensure the operation is associative (e.g., min, max, sum, gcd, bitwise operations).; Preprocessing takes O(N log N) time and space.
//   • Pitfalls: Not suitable for mutable arrays; updates require rebuilding the table.; Requires O(N log N) memory, which can be substantial for very large N.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number[][]} logs
 * @param {number} x
 * @param {number[]} queries
 * @return {number[]}
 */
var countServers = function(n, logs, x, queries) {
    const serverRequestTimes = new Map();
    for (const [serverId, time] of logs) {
        if (!serverRequestTimes.has(serverId)) {
            serverRequestTimes.set(serverId, []);
        }
        serverRequestTimes.get(serverId).push(time);
    }
    for (const times of serverRequestTimes.values()) {
        times.sort((a, b) => a - b);
    }
    const result = [];
    for (const query of queries) {
        let count = 0;
        for (const times of serverRequestTimes.values()) {
            const startTime = query - x;
            const endTime = query;
            let left = 0, right = times.length - 1;
            let hasRequestInRange = false;
            while (left <= right) {
                const mid = Math.floor((left + right) / 2);
                if (times[mid] >= startTime && times[mid] <= endTime) {
                    hasRequestInRange = true;
                    break;
                }
                if (times[mid] < startTime) {
                    left = mid + 1;
                }
                else {                    right = mid - 1;
                }
            }
            if (!hasRequestInRange) {
                count++;
            }
        }
        result.push(count);
    }
    return result;
};
