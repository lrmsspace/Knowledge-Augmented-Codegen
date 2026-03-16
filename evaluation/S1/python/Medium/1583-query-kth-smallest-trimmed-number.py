# Source: https://leetcode.com/problems/query-kth-smallest-trimmed-number/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array of strings nums, where each string is of equal length and consists of only digits.
#
# You are also given a 0-indexed 2D integer array queries where queries[i] = [ki, trimi]. For each queries[i], you need to:
#
#
# 	Trim each number in nums to its rightmost trimi digits.
# 	Determine the index of the kith smallest trimmed number in nums. If two trimmed numbers are equal, the number with the lower index is considered to be smaller.
# 	Reset each number in nums to its original length.
#
#
# Return an array answer of the same length as queries, where answer[i] is the answer to the ith query.
#
# Note:
#
#
# 	To trim to the rightmost x digits means to keep removing the leftmost digit, until only x digits remain.
# 	Strings in nums may contain leading zeros.
#
# Example:
# Input: nums = ["102","473","251","814"], queries = [[1,1],[2,3],[4,2],[1,2]]
# Output: [2,2,1,0]
# Explanation:
# 1. After trimming to the last digit, nums = ["2","3","1","4"]. The smallest number is 1 at index 2.
# 2. Trimmed to the last 3 digits, nums is unchanged. The 2nd smallest number is 251 at index 2.
# 3. Trimmed to the last 2 digits, nums = ["02","73","51","14"]. The 4th smallest number is 73.
# 4. Trimmed to the last 2 digits, the smallest number is 2 at index 0.
#    Note that the trimmed number "02" is evaluated as 2.
#
# Constraints:
# 1 <= nums.length <= 100
# 	1 <= nums[i].length <= 100
# 	nums[i] consists of only digits.
# 	All nums[i].length are equal.
# 	1 <= queries.length <= 100
# 	queries[i].length == 2
# 	1 <= ki <= nums.length
# 	1 <= trimi <= nums[i].length
#
#
#  
# Follow up: Could you use the Radix Sort Algorithm to solve this problem? What will be the complexity of that solution?
#
# Helpful references (internal KB):
# -  
# Kth order statistic in O(N) (array, enumeration)
#   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
#   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
#   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
#   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
#   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
# - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
#   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
#   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
#   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
#   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
#   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
# - Primality tests (number, enumeration, simulation)
#   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
#   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
#   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
#   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
#   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def smallestTrimmedNumbers(self, nums, queries):
        """
        :type nums: List[str]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        res = []
        for k, trim in queries:
            trimmed_nums = [(num[-trim:], i) for i, num in enumerate(nums)]
            trimmed_nums.sort()
            res.append(trimmed_nums[k - 1][1])
        return res