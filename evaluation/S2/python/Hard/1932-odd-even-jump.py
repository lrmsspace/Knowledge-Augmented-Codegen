# Source: https://leetcode.com/problems/odd-even-jump/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array arr. From some starting index, you can make a series of jumps. The (1st, 3rd, 5th, ...) jumps in the series are called odd-numbered jumps, and the (2nd, 4th, 6th, ...) jumps in the series are called even-numbered jumps. Note that the jumps are numbered, not the indices.
#
# You may jump forward from index i to index j (with i < j) in the following way:
#
#
# 	During odd-numbered jumps (i.e., jumps 1, 3, 5, ...), you jump to the index j such that arr[i] <= arr[j] and arr[j] is the smallest possible value. If there are multiple such indices j, you can only jump to the smallest such index j.
# 	During even-numbered jumps (i.e., jumps 2, 4, 6, ...), you jump to the index j such that arr[i] >= arr[j] and arr[j] is the largest possible value. If there are multiple such indices j, you can only jump to the smallest such index j.
# 	It may be the case that for some index i, there are no legal jumps.
#
#
# A starting index is good if, starting from that index, you can reach the end of the array (index arr.length - 1) by jumping some number of times (possibly 0 or more than once).
#
# Return the number of good starting indices.
#
# Example:
# Input: arr = [10,13,12,14,15]
# Output: 2
# Explanation: 
# From starting index i = 0, we can make our 1st jump to i = 2 (since arr[2] is the smallest among arr[1], arr[2], arr[3], arr[4] that is greater or equal to arr[0]), then we cannot jump any more.
# From starting index i = 1 and i = 2, we can make our 1st jump to i = 3, then we cannot jump any more.
# From starting index i = 3, we can make our 1st jump to i = 4, so we have reached the end.
# From starting index i = 4, we have reached the end already.
# In total, there are 2 different starting indices i = 3 and i = 4, where we can reach the end with some number of
# jumps.
#
# Constraints:
# 1 <= arr.length <= 2 * 104
# 	0 <= arr[i] < 105
#
# Helpful references (internal KB):
# - Longest increasing subsequence (array, dp-1d)
#   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
#   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
#   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
#   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
#   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
# - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
#   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
#   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
#   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
#   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
#   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
# - Scheduling jobs on two machines (array, greedy)
#   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
#   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
#   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
#   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
#   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def oddEvenJumps(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        n = len(arr)
        if n == 1:
            return 1

        # next_higher[i] = j means from index i, the next odd jump goes to index j
        # next_lower[i] = j means from index i, the next even jump goes to index j
        next_higher = [-1] * n
        next_lower = [-1] * n

        # Sort indices by the values in arr for odd jumps
        sorted_indices = sorted(range(n), key=lambda i: (arr[i], i))
        stack = []
        for i in sorted_indices:
            while stack and stack[-1] < i:
                next_higher[stack.pop()] = i
            stack.append(i)

        # Sort indices by the values in arr for even jumps
        sorted_indices = sorted(range(n), key=lambda i: (arr[i], -i))
        stack = []
        for i in sorted_indices:
            while stack and stack[-1] < i:
                next_lower[stack.pop()] = i
            stack.append(i)

        can_reach_end_from_odd = [False] * n
        can_reach_end_from_even = [False] * n
        can_reach_end_from_odd[-1] = True
        can_reach_end_from_even[-1] = True

        for i in range(n - 2, -1, -1):
            if next_higher[i] != -1:
                can_reach_end_from_odd[i] = can_reach_end_from_even[next_higher[i]]
            if next_lower[i] != -1:
                can_reach_end_from_even[i] = can_reach_end_from_odd[next_lower[i]]

        return sum(can_reach_end_from_odd)