# Source: https://leetcode.com/problems/find-servers-that-handled-most-number-of-requests/   |   Difficulty: Hard
#
# Problem Description:
# You have k servers numbered from 0 to k-1 that are being used to handle multiple requests simultaneously. Each server has infinite computational capacity but cannot handle more than one request at a time. The requests are assigned to servers according to a specific algorithm:
#
#
# 	The ith (0-indexed) request arrives.
# 	If all servers are busy, the request is dropped (not handled at all).
# 	If the (i % k)th server is available, assign the request to that server.
# 	Otherwise, assign the request to the next available server (wrapping around the list of servers and starting from 0 if necessary). For example, if the ith server is busy, try to assign the request to the (i+1)th server, then the (i+2)th server, and so on.
#
#
# You are given a strictly increasing array arrival of positive integers, where arrival[i] represents the arrival time of the ith request, and another array load, where load[i] represents the load of the ith request (the time it takes to complete). Your goal is to find the busiest server(s). A server is considered busiest if it handled the most number of requests successfully among all the servers.
#
# Return a list containing the IDs (0-indexed) of the busiest server(s). You may return the IDs in any order.
#
# Example:
# Input: k = 3, arrival = [1,2,3,4,5], load = [5,2,3,3,3] 
# Output: [1] 
# Explanation: 
# All of the servers start out available.
# The first 3 requests are handled by the first 3 servers in order.
# Request 3 comes in. Server 0 is busy, so it's assigned to the next available server, which is 1.
# Request 4 comes in. It cannot be handled since all servers are busy, so it is dropped.
# Servers 0 and 2 handled one request each, while server 1 handled two requests. Hence server 1 is the busiest server.
#
# Constraints:
# 1 <= k <= 105
# 	1 <= arrival.length, load.length <= 105
# 	arrival.length == load.length
# 	1 <= arrival[i], load[i] <= 109
# 	arrival is strictly increasing.
#
# Helpful references (internal KB):
# - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
#   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
#   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
#   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
#   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
#   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
# - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
#   • When to use: When you need O(1) query time for any associative operation (like sum, min, max, GCD) on a static array, after an O(N log N) preprocessing step.
#   • Idea: A Disjoint Sparse Table is a data structure that supports O(1) range queries for any associative operation on a static array. It achieves this by precomputing results for specific disjoint and overlapping ranges, with an O(N log N) construction time and space complexity.
#   • Invariants: table[k][i] stores the result of the operation for a range of length 2^k starting at index i.; For any query [L, R], the result is obtained by combining two precomputed values from blocks that cover [L, mid] and [mid+1, R].
#   • Tips: Understand the block decomposition based on powers of two for construction.; Queries combine results from two precomputed blocks that cover the query range.
#   • Pitfalls: Does not support point updates efficiently; any modification requires a full rebuild.; Higher space complexity of O(N log N) compared to some other range query structures.
# - kth-largest-element-in-an-array (array, merge-sort)
#   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
#   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
#   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
#   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
#   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def busiestServers(self, k, arrival, load):
        """
        :type k: int
        :type arrival: List[int]
        :type load: List[int]
        :rtype: List[int]
        """
        import heapq
        from sortedcontainers import SortedList
        
        busy_servers = []  # Min-heap of (end_time, server_id)
        available_servers = SortedList(range(k))  # Sorted list of available server IDs
        request_count = [0] * k  # Count of requests handled by each server
        
        for i in range(len(arrival)):
            # Free up servers that have completed their tasks
            while busy_servers and busy_servers[0][0] <= arrival[i]:
                end_time, server_id = heapq.heappop(busy_servers)
                available_servers.add(server_id)
            
            if not available_servers:
                continue  # No servers available, drop the request
            
            # Find the server to handle the request
            idx = available_servers.bisect_left(i % k)
            if idx == len(available_servers):
                idx = 0  # Wrap around to the beginning
            
            server_id = available_servers[idx]
            available_servers.remove(server_id)  # Mark this server as busy
            heapq.heappush(busy_servers, (arrival[i] + load[i], server_id))  # Add to busy servers
            request_count[server_id] += 1  # Increment request count for this server
        
        max_requests = max(request_count)
        return [i for i in range(k) if request_count[i] == max_requests]