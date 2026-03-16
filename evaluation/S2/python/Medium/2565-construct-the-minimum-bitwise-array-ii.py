# Source: https://leetcode.com/problems/construct-the-minimum-bitwise-array-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array nums consisting of n prime integers.
#
# You need to construct an array ans of length n, such that, for each index i, the bitwise OR of ans[i] and ans[i] + 1 is equal to nums[i], i.e. ans[i] OR (ans[i] + 1) == nums[i].
#
# Additionally, you must minimize each value of ans[i] in the resulting array.
#
# If it is not possible to find such a value for ans[i] that satisfies the condition, then set ans[i] = -1.
#
# Example:
# Input: nums = [2,3,5,7]
#
# Output: [-1,1,4,3]
#
# Explanation:
#
#
# 	For i = 0, as there is no value for ans[0] that satisfies ans[0] OR (ans[0] + 1) = 2, so ans[0] = -1.
# 	For i = 1, the smallest ans[1] that satisfies ans[1] OR (ans[1] + 1) = 3 is 1, because 1 OR (1 + 1) = 3.
# 	For i = 2, the smallest ans[2] that satisfies ans[2] OR (ans[2] + 1) = 5 is 4, because 4 OR (4 + 1) = 5.
# 	For i = 3, the smallest ans[3] that satisfies ans[3] OR (ans[3] + 1) = 7 is 3, because 3 OR (3 + 1) = 7.
#
# Constraints:
# 1 <= nums.length <= 100
# 	2 <= nums[i] <= 109
# 	nums[i] is a prime number.
#
# Helpful references (internal KB):
# - Linear Sieve (array, sieve)
#   • When to use: Use when you need to find the smallest prime factor or full prime factorization for all numbers up to a given limit N in linear time. It's particularly useful for tasks requiring precomputed factorizations.
#   • Idea: The Linear Sieve computes the smallest prime factor for every number up to N, ensuring each composite number is marked exactly once by its smallest prime factor. It achieves this in O(N) time complexity.
#   • Invariants: Every number `i` from 2 to N has its `lp[i]` correctly set to its smallest prime factor.; The `primes` array contains all prime numbers less than or equal to the current iteration `i`.
#   • Tips: Stores the smallest prime factor (lp) for each number.; Efficiently generates all prime numbers up to N.
#   • Pitfalls: Higher memory usage compared to the classic Sieve of Eratosthenes due to storing lp array.; Can be slower in practice than optimized Sieve of Eratosthenes for merely generating primes.
# - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
#   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
#   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
#   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
#   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
#   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
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
    def minBitwiseArray(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        ans = []
        for num in nums:
            if num & (num + 1) == 0:
                ans.append(num - 1)
            else:
                ans.append(-1)
        return ans