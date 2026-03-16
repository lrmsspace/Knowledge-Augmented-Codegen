# Source: https://leetcode.com/problems/closest-room/   |   Difficulty: Hard
#
# Problem Description:
# There is a hotel with n rooms. The rooms are represented by a 2D integer array rooms where rooms[i] = [roomIdi, sizei] denotes that there is a room with room number roomIdi and size equal to sizei. Each roomIdi is guaranteed to be unique.
#
# You are also given k queries in a 2D array queries where queries[j] = [preferredj, minSizej]. The answer to the jth query is the room number id of a room such that:
#
#
# 	The room has a size of at least minSizej, and
# 	abs(id - preferredj) is minimized, where abs(x) is the absolute value of x.
#
#
# If there is a tie in the absolute difference, then use the room with the smallest such id. If there is no such room, the answer is -1.
#
# Return an array answer of length k where answer[j] contains the answer to the jth query.
#
# Example:
# Input: rooms = [[2,2],[1,2],[3,2]], queries = [[3,1],[3,3],[5,2]]
# Output: [3,-1,3]
# Explanation: The answers to the queries are as follows:
# Query = [3,1]: Room number 3 is the closest as abs(3 - 3) = 0, and its size of 2 is at least 1. The answer is 3.
# Query = [3,3]: There are no rooms with a size of at least 3, so the answer is -1.
# Query = [5,2]: Room number 3 is the closest as abs(3 - 5) = 2, and its size of 2 is at least 2. The answer is 3.
#
# Constraints:
# n == rooms.length
# 	1 <= n <= 105
# 	k == queries.length
# 	1 <= k <= 104
# 	1 <= roomIdi, preferredj <= 107
# 	1 <= sizei, minSizej <= 107
#
# Helpful references (internal KB):
# - Range Minimum Query (array, sparse-table)
#   • When to use: When performing many range minimum queries on a static array, especially when query time needs to be logarithmic after initial preprocessing.
#   • Idea: A data structure that precomputes minimums for all possible ranges of power-of-two lengths, allowing O(1) query time after O(N log N) preprocessing. It efficiently answers range minimum queries on an immutable array.
#   • Invariants: For any `j`, `dp[i][j]` stores the minimum value in the segment starting at `i` with length `2^j`.; The `log_table[k]` stores `floor(log2(k))` for efficient length calculation.
#   • Tips: Precompute log values or use `std::log2` for efficient length calculations.; The `dp[i][j]` entry stores the minimum in the range `[i, i + 2^j - 1]`.
#   • Pitfalls: Does not support updates to the array elements; it's for static data only.; Higher memory consumption compared to some other range query structures.
# - Lowest Common Ancestor - Tarjan's off-line algorithm (tree, ds, dfs, union-find)
#   • When to use: Use when you need to answer multiple Lowest Common Ancestor (LCA) queries on a static tree, and all queries are available before processing.
#   • Idea: Tarjan's off-line LCA algorithm efficiently computes the Lowest Common Ancestor for multiple pairs of nodes in a tree using a single Depth-First Search traversal combined with a Disjoint Set Union data structure, achieving nearly linear time complexity.
#   • Invariants: When DFS is at node `v`, all its children's subtrees have been fully processed and merged into `v`'s DSU set.; For any node `x` whose DFS has completed, `ancestor[find_set(x)]` stores an ancestor of `x` on the path to the root.
#   • Tips: Initialize each node as its own set in DSU with itself as the ancestor.; Process queries for a node only after its children's subtrees are fully processed.
#   • Pitfalls: Not suitable for online LCA queries or dynamic tree structures.; Incorrectly updating the `ancestor` array in the DSU can lead to wrong LCAs.
# - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
#   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
#   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
#   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
#   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
#   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def closestRoom(self, rooms, queries):
        """
        :type rooms: List[List[int]]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        # Sort rooms by size in descending order
        rooms.sort(key=lambda x: x[1], reverse=True)

        # Sort queries by minSize in descending order, while keeping track of original indices
        indexed_queries = sorted(enumerate(queries), key=lambda x: x[1][1], reverse=True)

        result = [-1] * len(queries)  # Initialize result with -1
        available_rooms = []  # This will store the room numbers of available rooms
        room_index = 0  # Pointer for rooms

        for idx, (preferred, min_size) in indexed_queries:
            # Add all rooms that meet the min_size requirement to the available_rooms list
            while room_index < len(rooms) and rooms[room_index][1] >= min_size:
                available_rooms.append(rooms[room_index][0])
                room_index += 1

            if not available_rooms:
                continue  # No rooms available for this query

            # Find the closest room number to preferred using binary search
            available_rooms.sort()  # Sort available rooms by room number
            pos = self.binary_search_closest(available_rooms, preferred)
            result[idx] = available_rooms[pos]

        return result