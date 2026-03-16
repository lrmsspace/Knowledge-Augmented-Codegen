# Source: https://leetcode.com/problems/friends-of-appropriate-ages/   |   Difficulty: Medium
#
# Problem Description:
# There are n persons on a social media website. You are given an integer array ages where ages[i] is the age of the ith person.
#
# A Person x will not send a friend request to a person y (x != y) if any of the following conditions is true:
#
#
# 	age[y] <= 0.5 * age[x] + 7
# 	age[y] > age[x]
# 	age[y] > 100 && age[x] < 100
#
#
# Otherwise, x will send a friend request to y.
#
# Note that if x sends a request to y, y will not necessarily send a request to x. Also, a person will not send a friend request to themself.
#
# Return the total number of friend requests made.
#
# Example:
# Input: ages = [16,16]
# Output: 2
# Explanation: 2 people friend request each other.
#
# Constraints:
# n == ages.length
# 	1 <= n <= 2 * 104
# 	1 <= ages[i] <= 120
#
# Helpful references (internal KB):
# - The Inclusion-Exclusion Principle (string, counting)
#   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
#   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
#   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
#   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
#   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
# - MEX (minimal excluded) of a sequence (array, enumeration)
#   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
#   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
#   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
#   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
#   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
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
    def numFriendRequests(self, ages):
        """
        :type ages: List[int]
        :rtype: int
        """
        count = [0] * 121
        for age in ages:
            count[age] += 1

        total_requests = 0
        for ageA in range(1, 121):
            if count[ageA] == 0:
                continue
            for ageB in range(1, 121):
                if count[ageB] == 0:
                    continue
                if ageB <= 0.5 * ageA + 7:
                    continue
                if ageB > ageA:
                    continue
                if ageB > 100 and ageA < 100:
                    continue
                total_requests += count[ageA] * count[ageB]
                if ageA == ageB:
                    total_requests -= count[ageA]  # Remove self-requests

        return total_requests