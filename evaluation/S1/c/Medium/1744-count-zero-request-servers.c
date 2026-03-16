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
// - Search for a pair of intersecting segments (geometry, enumeration, sweep-line)
//   • When to use: When needing to efficiently detect if any two line segments among a given set intersect, or to find one such intersecting pair.
//   • Idea: This algorithm efficiently determines if any two line segments in a given set intersect by processing events along a sweep line, typically achieving O(N log N) time complexity.
//   • Invariants: All segments fully to the left of the sweep line have been processed and do not intersect each other.; The active set contains all segments currently intersecting the sweep line, ordered by their y-coordinate.
//   • Tips: Represent segments by their endpoints as event points, sorted by x-coordinate.; Use a balanced binary search tree (or similar structure) to maintain active segments ordered by their y-coordinate at the sweep line.
//   • Pitfalls: Floating point precision issues can lead to incorrect intersection detection or ordering.; Degenerate cases like collinear segments or multiple segments intersecting at a single point.
// - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
//   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
//   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
//   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
//   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
//   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countServers(int n, int** logs, int logsSize, int* logsColSize, int x, int* queries, int queriesSize, int* returnSize) {
   
    // Hash map functions
    unsigned int hash(int val, int left, int right) {
        unsigned int h = 5381;
        h = ((h << 5) + h) + val;
        h = ((h << 5) + h) + left;
        h = ((h << 5) + h) + right;
        return h % BUCKETS;
    }

    struct Entry* find_or_insert(struct Ctx* ctx, int val, int left, int right) {
        unsigned int h = hash(val, left, right);
        struct Entry* curr = ctx->buckets[h];
        while (curr) {
            if (curr->val == val && curr->left == left && curr->right == right) {
                return curr;
            }
            curr = curr->next;
        }
        struct Entry* newEntry = (struct Entry*)malloc(sizeof(struct Entry));
        newEntry->val = val;
        newEntry->left = left;
        newEntry->right = right;
        newEntry->id = ctx->capacity++;
        newEntry->next = ctx->buckets[h];
        ctx->buckets[h] = newEntry;
        return newEntry;
    }

    // Context initialization
    struct Ctx ctx;
    ctx.buckets = (struct Entry**)calloc(BUCKETS, sizeof(struct Entry*));
    ctx.capacity = 0;
    ctx.counts = (int*)calloc(100000, sizeof(int));

    // Process logs
    for (int i = 0; i < logsSize; i++) {
        int server_id = logs[i][0];
        int time = logs[i][1];
        struct Entry* entry = find_or_insert(&ctx, server_id, time - x, time);
        ctx.counts[entry->id]++;
    }

    // Prepare result
    int* result = (int*)malloc(queriesSize * sizeof(int));
    for (int i = 0; i < queriesSize; i++) {
        int query_time = queries[i];
        int zero_count = 0;
        for (int j = 1; j <= n; j++) {
            struct Entry* entry = find_or_insert(&ctx, j, query_time - x, query_time);
            if (ctx.counts[entry->id] == 0) {
                zero_count++;
            }
        }
        result[i] = zero_count;
        
    }
    *returnSize = queriesSize;
    return result;
}
