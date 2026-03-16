# Source: https://leetcode.com/problems/handling-sum-queries-after-update/   |   Difficulty: Hard
#
# Problem Description:
# You are given two 0-indexed arrays nums1 and nums2 and a 2D array queries of queries. There are three types of queries:
#
#
# 	For a query of type 1, queries[i] = [1, l, r]. Flip the values from 0 to 1 and from 1 to 0 in nums1 from index l to index r. Both l and r are 0-indexed.
# 	For a query of type 2, queries[i] = [2, p, 0]. For every index 0 <= i < n, set nums2[i] = nums2[i] + nums1[i] * p.
# 	For a query of type 3, queries[i] = [3, 0, 0]. Find the sum of the elements in nums2.
#
#
# Return an array containing all the answers to the third type queries.
#
# Example:
# Input: nums1 = [1,0,1], nums2 = [0,0,0], queries = [[1,1,1],[2,1,0],[3,0,0]]
# Output: [3]
# Explanation: After the first query nums1 becomes [1,1,1]. After the second query, nums2 becomes [1,1,1], so the answer to the third query is 3. Thus, [3] is returned.
#
# Constraints:
# 1 <= nums1.length,nums2.length <= 105
# 	nums1.length = nums2.length
# 	1 <= queries.length <= 105
# 	queries[i].length = 3
# 	0 <= l <= r <= nums1.length - 1
# 	0 <= p <= 106
# 	0 <= nums1[i] <= 1
# 	0 <= nums2[i] <= 109
#
# Helpful references (internal KB):
# - Segment Tree (tree, array, segment-tree, recursion, divide-and-conquer)
#   • When to use: Use for efficient range queries and updates on an array. It handles aggregated information over dynamic intervals.
#   • Idea: A segment tree is a tree data structure used for storing information about intervals or segments. It allows answering range queries and range updates in logarithmic time, making it efficient for dynamic array problems.
#   • Invariants: Each node represents a contiguous segment of the original array.; The value stored in a parent node is an aggregation of its children's values.
#   • Tips: Build the tree recursively, dividing the array into halves.; Each node stores an aggregate value for its corresponding segment.
#   • Pitfalls: Incorrectly handling array indexing (0-based vs 1-based).; Off-by-one errors in segment boundaries during queries/updates.
# - Counting labeled graphs (number, dp-2d, counting, recursion)
#   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
#   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
#   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
#   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
#   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def handleQuery(self, nums1, nums2, queries):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        n = len(nums1)
        sum_nums2 = sum(nums2)
        count_ones = sum(nums1)
        result = []

        for query in queries:
            if query[0] == 1:
                l, r = query[1], query[2]
                length = r - l + 1
                # Calculate how many 1s are flipped to 0s and how many 0s are flipped to 1s
                ones_to_zeroes = min(count_ones, length)  # At most count_ones can be flipped to zero
                zeroes_to_ones = length - ones_to_zeroes   # The rest will be flipped to one

                count_ones += zeroes_to_ones - ones_to_zeroes
            elif query[0] == 2:
                p = query[1]
                sum_nums2 += count_ones * p
            else:  # query[0] == 3
                result.append(sum_nums2)

        return result