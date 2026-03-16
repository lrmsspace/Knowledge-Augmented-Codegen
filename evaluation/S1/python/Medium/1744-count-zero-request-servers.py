# Source: https://leetcode.com/problems/count-zero-request-servers/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n denoting the total number of servers and a 2D 0-indexed integer array logs, where logs[i] = [server_id, time] denotes that the server with id server_id received a request at time time.
#
# You are also given an integer x and a 0-indexed integer array queries.
#
# Return a 0-indexed integer array arr of length queries.length where arr[i] represents the number of servers that did not receive any requests during the time interval [queries[i] - x, queries[i]].
#
# Note that the time intervals are inclusive.
#
# Example:
# Input: n = 3, logs = [[1,3],[2,6],[1,5]], x = 5, queries = [10,11]
# Output: [1,2]
# Explanation: 
# For queries[0]: The servers with ids 1 and 2 get requests in the duration of [5, 10]. Hence, only server 3 gets zero requests.
# For queries[1]: Only the server with id 2 gets a request in duration of [6,11]. Hence, the servers with ids 1 and 3 are the only servers that do not receive any requests during that time period.
#
# Constraints:
# 1 <= n <= 105
# 	1 <= logs.length <= 105
# 	1 <= queries.length <= 105
# 	logs[i].length == 2
# 	1 <= logs[i][0] <= n
# 	1 <= logs[i][1] <= 106
# 	1 <= x <= 105
# 	x < queries[i] <= 106
#
# Helpful references (internal KB):
# - Range Minimum Query (array, sparse-table)
#   • When to use: When performing many range minimum queries on a static array, especially when query time needs to be logarithmic after initial preprocessing.
#   • Idea: A data structure that precomputes minimums for all possible ranges of power-of-two lengths, allowing O(1) query time after O(N log N) preprocessing. It efficiently answers range minimum queries on an immutable array.
#   • Invariants: For any `j`, `dp[i][j]` stores the minimum value in the segment starting at `i` with length `2^j`.; The `log_table[k]` stores `floor(log2(k))` for efficient length calculation.
#   • Tips: Precompute log values or use `std::log2` for efficient length calculations.; The `dp[i][j]` entry stores the minimum in the range `[i, i + 2^j - 1]`.
#   • Pitfalls: Does not support updates to the array elements; it's for static data only.; Higher memory consumption compared to some other range query structures.
# - Search for a pair of intersecting segments (geometry, enumeration, sweep-line)
#   • When to use: When needing to efficiently detect if any two line segments among a given set intersect, or to find one such intersecting pair.
#   • Idea: This algorithm efficiently determines if any two line segments in a given set intersect by processing events along a sweep line, typically achieving O(N log N) time complexity.
#   • Invariants: All segments fully to the left of the sweep line have been processed and do not intersect each other.; The active set contains all segments currently intersecting the sweep line, ordered by their y-coordinate.
#   • Tips: Represent segments by their endpoints as event points, sorted by x-coordinate.; Use a balanced binary search tree (or similar structure) to maintain active segments ordered by their y-coordinate at the sweep line.
#   • Pitfalls: Floating point precision issues can lead to incorrect intersection detection or ordering.; Degenerate cases like collinear segments or multiple segments intersecting at a single point.
# - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
#   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
#   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
#   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
#   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
#   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countServers(self, n, logs, x, queries):
        """
        :type n: int
        :type logs: List[List[int]]
        :type x: int
        :type queries: List[int]
        :rtype: List[int]
        """
        from collections import defaultdict
        import bisect

        # Preprocess logs to map each server to its request times
        server_requests = defaultdict(list)
        for server_id, time in logs:
            server_requests[server_id].append(time)

        # Sort the request times for each server
        for server_id in server_requests:
            server_requests[server_id].sort()

        result = []
        for query in queries:
            start_time = query - x
            zero_request_count = 0

            for server_id in range(1, n + 1):
                if server_id not in server_requests:
                    zero_request_count += 1
                    continue

                times = server_requests[server_id]
                # Find the number of requests in the interval [start_time, query]
                left_index = bisect.bisect_left(times, start_time)
                right_index = bisect.bisect_right(times, query)

                if left_index == right_index:
                    zero_request_count += 1

            result.append(zero_request_count)

        return result