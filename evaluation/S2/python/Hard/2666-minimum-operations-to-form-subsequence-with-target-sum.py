# Source: https://leetcode.com/problems/minimum-operations-to-form-subsequence-with-target-sum/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed array nums consisting of non-negative powers of 2, and an integer target.
#
# In one operation, you must apply the following changes to the array:
#
#
# 	Choose any element of the array nums[i] such that nums[i] > 1.
# 	Remove nums[i] from the array.
# 	Add two occurrences of nums[i] / 2 to the end of nums.
#
#
# Return the minimum number of operations you need to perform so that nums contains a subsequence whose elements sum to target. If it is impossible to obtain such a subsequence, return -1.
#
# A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
#
# Example:
# Input: nums = [1,2,8], target = 7
# Output: 1
# Explanation: In the first operation, we choose element nums[2]. The array becomes equal to nums = [1,2,4,4].
# At this stage, nums contains the subsequence [1,2,4] which sums up to 7.
# It can be shown that there is no shorter sequence of operations that results in a subsequnce that sums up to 7.
#
# Constraints:
# 1 <= nums.length <= 1000
# 	1 <= nums[i] <= 230
# 	nums consists only of non-negative powers of two.
# 	1 <= target < 231
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
#   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
#   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
#   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
#   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
#   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
# - 0-1 BFS (graph, array, dijkstra, bfs)
#   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
#   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
#   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
#   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
#   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
# - Range Minimum Query (array, bitset, bit-fenwick)
#   • When to use: When you need to efficiently query the minimum value within a range and perform point updates on an array. It's suitable for scenarios requiring logarithmic time complexity for both operations.
#   • Idea: A Fenwick tree (BIT) can be adapted to answer Range Minimum Queries and perform point updates in O(log N) time. It achieves this by storing prefix minimums in a tree-like structure, allowing efficient aggregation.
#   • Invariants: Each node `tree[i]` stores the minimum of a specific range `[i - (i & -i) + 1, i]`.; An update to `arr[idx]` correctly propagates the new minimum to all relevant `tree` nodes.
#   • Tips: Adapt standard BIT operations for minimums instead of sums.; Use `min(current_value, new_value)` for updates and queries.
#   • Pitfalls: Standard BIT operations are for sums; direct application for minimums is incorrect.; Querying a range `[L, R]` for minimum is not a simple `query(R) - query(L-1)`.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minOperations(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        from collections import Counter
        count = Counter(nums)
        operations = 0

        for i in range(31):
            bit = (target >> i) & 1
            if bit == 1:
                if count[1 << i] > 0:
                    count[1 << i] -= 1
                else:
                    j = i + 1
                    while j < 31 and count[1 << j] == 0:
                        j += 1
                    if j == 31:
                        return -1
                    while j > i:
                        count[1 << j] -= 1
                        count[1 << (j - 1)] += 2
                        operations += 1
                        j -= 1
                    count[1 << i] -= 1

            count[1 << (i + 1)] += count[1 << i] // 2

        return operations