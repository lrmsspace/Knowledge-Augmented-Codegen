# Source: https://leetcode.com/problems/binary-prefix-divisible-by-5/   |   Difficulty: Easy
#
# Problem Description:
# You are given a binary array nums (0-indexed).
#
# We define xi as the number whose binary representation is the subarray nums[0..i] (from most-significant-bit to least-significant-bit).
#
#
# 	For example, if nums = [1,0,1], then x0 = 1, x1 = 2, and x2 = 5.
#
#
# Return an array of booleans answer where answer[i] is true if xi is divisible by 5.
#
# Example:
# Input: nums = [0,1,1]
# Output: [true,false,false]
# Explanation: The input numbers in binary are 0, 01, 011; which are 0, 1, and 3 in base-10.
# Only the first number is divisible by 5, so answer[0] is true.
#
# Constraints:
# 1 <= nums.length <= 105
# 	nums[i] is either 0 or 1.
#
# Helpful references (internal KB):
# - Submask Enumeration
#  (number, bitset, enumeration)
#   • When to use: When you need to iterate through all possible submasks of a given bitmask efficiently, typically for problems involving subsets or combinations represented by bits.
#   • Idea: This algorithm efficiently iterates through all submasks of a given bitmask in descending order using a clever bitwise trick. It processes each submask in O(1) time, leading to an overall complexity of O(2^k) where k is the number of set bits in the original mask.
#   • Invariants: Each `s` generated is a valid submask of the original mask `m`.; The value of `s` strictly decreases in each iteration until it reaches 0 (or the loop terminates).
#   • Tips: Always consider processing the submask 0 separately if it's a valid case for your problem.; The iteration naturally generates submasks in strictly descending numerical order.
#   • Pitfalls: Forgetting that the standard loop structure `for (int s = m; s > 0; s = (s - 1) & m)` omits submask 0.; Incorrectly assuming the iteration order is ascending; it is always descending.
# - Primality tests (number, enumeration, simulation)
#   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
#   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
#   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
#   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
#   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
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
    def prefixesDivBy5(self, nums):
        """
        :type nums: List[int]
        :rtype: List[bool]
        """
        result = []
        current_value = 0
        for bit in nums:
            current_value = ((current_value << 1) | bit) % 5
            result.append(current_value == 0)
        return result