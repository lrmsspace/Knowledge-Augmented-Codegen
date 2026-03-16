# Source: https://leetcode.com/problems/maximum-number-of-achievable-transfer-requests/   |   Difficulty: Hard
#
# Problem Description:
# We have n buildings numbered from 0 to n - 1. Each building has a number of employees. It's transfer season, and some employees want to change the building they reside in.
#
# You are given an array requests where requests[i] = [fromi, toi] represents an employee's request to transfer from building fromi to building toi.
#
# All buildings are full, so a list of requests is achievable only if for each building, the net change in employee transfers is zero. This means the number of employees leaving is equal to the number of employees moving in. For example if n = 3 and two employees are leaving building 0, one is leaving building 1, and one is leaving building 2, there should be two employees moving to building 0, one employee moving to building 1, and one employee moving to building 2.
#
# Return the maximum number of achievable requests.
#
# Example:
# Input: n = 5, requests = [[0,1],[1,0],[0,1],[1,2],[2,0],[3,4]]
# Output: 5
# Explantion: Let's see the requests:
# From building 0 we have employees x and y and both want to move to building 1.
# From building 1 we have employees a and b and they want to move to buildings 2 and 0 respectively.
# From building 2 we have employee z and they want to move to building 0.
# From building 3 we have employee c and they want to move to building 4.
# From building 4 we don't have any requests.
# We can achieve the requests of users x and b by swapping their places.
# We can achieve the requests of users y, a and z by swapping the places in the 3 buildings.
#
# Constraints:
# 1 <= n <= 20
# 	1 <= requests.length <= 16
# 	requests[i].length == 2
# 	0 <= fromi, toi < n
#
# Helpful references (internal KB):
# - Submask Enumeration
#  (number, bitset, enumeration, bitmask-dp)
#   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
#   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
#   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
#   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
#   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - The Inclusion-Exclusion Principle (array, number, counting, sieve)
#   • When to use: Use when direct counting of elements satisfying specific conditions is difficult due to overlaps, and you need to find the count of elements satisfying at least one, exactly k, or none of several properties.
#   • Idea: The Inclusion-Exclusion Principle counts the size of a union of sets by alternately adding and subtracting the sizes of intersections of increasing numbers of sets. Its complexity is often exponential in the number of properties.
#   • Invariants: At the start of processing subsets of size k, the running total correctly accounts for all intersections of size less than k.; For every element x, its contribution to the total sum is 1 if it satisfies the target condition, and 0 otherwise.
#   • Tips: Clearly define the properties (P1, P2, ..., Pn) for which elements are counted.; Systematically calculate the sizes of all relevant intersections of properties.
#   • Pitfalls: Incorrectly defining the properties or the universe of elements being counted.; Errors in calculating the sizes of specific intersections of properties.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumRequests(self, n, requests):
        """
        :type n: int
        :type requests: List[List[int]]
        :rtype: int
        """
        # 1. 枚举所有请求的子集
        m = len(requests)
        max_requests = 0

        for mask in range(1 << m):
            net_change = [0] * n
            count = 0

            for i in range(m):
                if mask & (1 << i):
                    from_building, to_building = requests[i]
                    net_change[from_building] -= 1
                    net_change[to_building] += 1
                    count += 1

            # 2. 检查 net_change 是否全为零
            if all(x == 0 for x in net_change):
                max_requests = max(max_requests, count)

        return max_requests