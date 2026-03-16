# Source: https://leetcode.com/problems/minimum-time-to-remove-all-cars-containing-illegal-goods/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed binary string s which represents a sequence of train cars. s[i] = '0' denotes that the ith car does not contain illegal goods and s[i] = '1' denotes that the ith car does contain illegal goods.
#
# As the train conductor, you would like to get rid of all the cars containing illegal goods. You can do any of the following three operations any number of times:
#
#
# 	Remove a train car from the left end (i.e., remove s[0]) which takes 1 unit of time.
# 	Remove a train car from the right end (i.e., remove s[s.length - 1]) which takes 1 unit of time.
# 	Remove a train car from anywhere in the sequence which takes 2 units of time.
#
#
# Return the minimum time to remove all the cars containing illegal goods.
#
# Note that an empty sequence of cars is considered to have no cars containing illegal goods.
#
# Example:
# Input: s = "1100101"
# Output: 5
# Explanation: 
# One way to remove all the cars containing illegal goods from the sequence is to
# - remove a car from the left end 2 times. Time taken is 2 * 1 = 2.
# - remove a car from the right end. Time taken is 1.
# - remove the car containing illegal goods found in the middle. Time taken is 2.
# This obtains a total time of 2 + 1 + 2 = 5. 
#
# An alternative way is to
# - remove a car from the left end 2 times. Time taken is 2 * 1 = 2.
# - remove a car from the right end 3 times. Time taken is 3 * 1 = 3.
# This also obtains a total time of 2 + 3 = 5.
#
# 5 is the minimum time taken to remove all the cars containing illegal goods. 
# There are no other ways to remove them with less time.
#
# Constraints:
# 1 <= s.length <= 2 * 105
# 	s[i] is either '0' or '1'.
#
# Helpful references (internal KB):
# - Sqrt Decomposition (array, enumeration, difference-array)
#   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
#   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
#   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
#   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
#   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Digit DP (array, number, digit-dp)
#   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
#   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
#   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
#   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
#   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumTime(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        left = 0
        right = n - 1
        time = 0

        while left <= right:
            if s[left] == '1' and s[right] == '1':
                # If both ends have illegal goods, remove the one that takes less time
                if left == right:  # Only one car left
                    time += 1
                    break
                else:
                    time += 2  # Removing from the middle takes 2 units of time
                    left += 1
                    right -= 1
            elif s[left] == '1':
                time += 1  # Removing from the left end takes 1 unit of time
                left += 1
            elif s[right] == '1':
                time += 1  # Removing from the right end takes 1 unit of time
                right -= 1
            else:
                # If both ends do not have illegal goods, just move inward
                left += 1
                right -= 1

        return time