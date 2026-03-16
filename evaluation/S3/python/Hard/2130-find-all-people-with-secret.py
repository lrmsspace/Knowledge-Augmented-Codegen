# Source: https://leetcode.com/problems/find-all-people-with-secret/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer n indicating there are n people numbered from 0 to n - 1. You are also given a 0-indexed 2D integer array meetings where meetings[i] = [xi, yi, timei] indicates that person xi and person yi have a meeting at timei. A person may attend multiple meetings at the same time. Finally, you are given an integer firstPerson.
#
# Person 0 has a secret and initially shares the secret with a person firstPerson at time 0. This secret is then shared every time a meeting takes place with a person that has the secret. More formally, for every meeting, if a person xi has the secret at timei, then they will share the secret with person yi, and vice versa.
#
# The secrets are shared instantaneously. That is, a person may receive the secret and share it with people in other meetings within the same time frame.
#
# Return a list of all the people that have the secret after all the meetings have taken place. You may return the answer in any order.
#
# Example:
# Input: n = 6, meetings = [[1,2,5],[2,3,8],[1,5,10]], firstPerson = 1
# Output: [0,1,2,3,5]
# Explanation:
# At time 0, person 0 shares the secret with person 1.
# At time 5, person 1 shares the secret with person 2.
# At time 8, person 2 shares the secret with person 3.
# At time 10, person 1 shares the secret with person 5.​​​​
# Thus, people 0, 1, 2, 3, and 5 know the secret after all the meetings.
#
# Constraints:
# 2 <= n <= 105
# 	1 <= meetings.length <= 105
# 	meetings[i].length == 3
# 	0 <= xi, yi <= n - 1
# 	xi != yi
# 	1 <= timei <= 105
# 	1 <= firstPerson <= n - 1
#
# Helpful references (internal KB):
# - Disjoint Set Union (ds, tree, array, union-find)
#   • When to use: Use when you need to efficiently manage a collection of disjoint sets, supporting operations to merge sets and determine if two elements belong to the same set.
#   • Idea: Disjoint Set Union (DSU) is a data structure that maintains a collection of disjoint sets and supports two primary operations: union (merging two sets) and find (determining the representative of an element's set). With path compression and union by rank/size, operations achieve nearly O(1) amortized time complexity.
#   • Invariants: For any element `v`, `parent[v]` is either `v` itself (if `v` is a root) or an ancestor of `v`.; All elements belonging to the same set share a common root representative.
#   • Tips: Apply path compression during `find_set` to optimize future queries.; Utilize union by rank or size to maintain balanced trees.
#   • Pitfalls: Omitting path compression or union by rank/size results in poor performance.; Failing to correctly identify the root of a set in `find_set`.
# - Disjoint Set Union (ds, tree, array, union-find)
#   • When to use: Use when you need to maintain a collection of disjoint sets and efficiently perform union operations to merge sets or find the representative of an element's set.
#   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. With path compression and union by rank/size, these operations achieve nearly constant amortized time complexity, O(alpha(N)).
#   • Invariants: Each element `v` is either a root (parent[v] == v) or has a parent pointer to another element in its set.; The `find_set` operation, after path compression, ensures that all nodes on the path from `v` to its root directly point to the root.
#   • Tips: Implement path compression in `find_set` for optimal performance.; Use union by rank or union by size to keep trees flat and balanced.
#   • Pitfalls: Forgetting path compression or union by rank/size leads to O(N) worst-case operations.; Incorrectly merging sets by only updating one root without considering the other's rank/size.
# - Search for a pair of intersecting segments (geometry, enumeration, sweep-line)
#   • When to use: When needing to efficiently detect if any two line segments among a given set intersect, or to find one such intersecting pair.
#   • Idea: This algorithm efficiently determines if any two line segments in a given set intersect by processing events along a sweep line, typically achieving O(N log N) time complexity.
#   • Invariants: All segments fully to the left of the sweep line have been processed and do not intersect each other.; The active set contains all segments currently intersecting the sweep line, ordered by their y-coordinate.
#   • Tips: Represent segments by their endpoints as event points, sorted by x-coordinate.; Use a balanced binary search tree (or similar structure) to maintain active segments ordered by their y-coordinate at the sweep line.
#   • Pitfalls: Floating point precision issues can lead to incorrect intersection detection or ordering.; Degenerate cases like collinear segments or multiple segments intersecting at a single point.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findAllPeople(self, n, meetings, firstPerson):
        """
        :type n: int
        :type meetings: List[List[int]]
        :type firstPerson: int
        :rtype: List[int]
        """
        from collections import defaultdict

        # Group meetings by time
        time_to_meetings = defaultdict(list)
        for x, y, t in meetings:
            time_to_meetings[t].append((x, y))

        # Sort times
        sorted_times = sorted(time_to_meetings.keys())

        # DSU implementation
        parent = list(range(n))
        rank = [1] * n

        def find_set(v):
            if parent[v] != v:
                parent[v] = find_set(parent[v])
            return parent[v]

        def union_sets(a, b):
            a = find_set(a)
            b = find_set(b)
            if a != b:
                if rank[a] < rank[b]:
                    a, b = b, a
                parent[b] = a
                if rank[a] == rank[b]:
                    rank[a] += 1

        # Initially, person 0 and firstPerson know the secret
        union_sets(0, firstPerson)

        for t in sorted_times:
            meetings_at_time = time_to_meetings[t]
            # Union all meetings at this time
            for x, y in meetings_at_time:
                union_sets(x, y)

            # After processing all meetings at this time, check who knows the secret
            secret_root = find_set(0)
            for x, y in meetings_at_time:
                if find_set(x) == secret_root or find_set(y) == secret_root:
                    union_sets(x, y)

        # Collect all people who know the secret
        result = []
        secret_root = find_set(0)
        for i in range(n):
            if find_set(i) == secret_root:
                result.append(i)

        return result