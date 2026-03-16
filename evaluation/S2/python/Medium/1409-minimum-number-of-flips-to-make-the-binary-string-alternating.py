# Source: https://leetcode.com/problems/minimum-number-of-flips-to-make-the-binary-string-alternating/   |   Difficulty: Medium
#
# Problem Description:
# You are given a binary string s. You are allowed to perform two types of operations on the string in any sequence:
#
#
# 	Type-1: Remove the character at the start of the string s and append it to the end of the string.
# 	Type-2: Pick any character in s and flip its value, i.e., if its value is '0' it becomes '1' and vice-versa.
#
#
# Return the minimum number of type-2 operations you need to perform such that s becomes alternating.
#
# The string is called alternating if no two adjacent characters are equal.
#
#
# 	For example, the strings "010" and "1010" are alternating, while the string "0100" is not.
#
# Example:
# Input: s = "111000"
# Output: 2
# Explanation: Use the first operation two times to make s = "100011".
# Then, use the second operation on the third and sixth elements to make s = "101010".
#
# Constraints:
# 1 <= s.length <= 105
# 	s[i] is either '0' or '1'.
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - palindrome-partitioning (string, two-pointers, simulation)
#   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
#   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
#   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
#   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
#   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
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
    def minFlips(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        s_double = s + s  # Concatenate the string to itself to handle rotations
        pattern1 = ''.join('0' if i % 2 == 0 else '1' for i in range(2 * n))  # "010101..."
        pattern2 = ''.join('1' if i % 2 == 0 else '0' for i in range(2 * n))  # "101010..."
        
        flips_pattern1 = flips_pattern2 = 0
        min_flips = float('inf')

        for i in range(2 * n):
            if s_double[i] != pattern1[i]:
                flips_pattern1 += 1
            if s_double[i] != pattern2[i]:
                flips_pattern2 += 1
            
            # Once we have processed n characters, we can start checking for minimum flips
            if i >= n - 1:
                min_flips = min(min_flips, flips_pattern1, flips_pattern2)
                
                # Remove the effect of the character that is sliding out of the window
                if s_double[i - n + 1] != pattern1[i - n + 1]:
                    flips_pattern1 -= 1
                if s_double[i - n + 1] != pattern2[i - n + 1]:
                    flips_pattern2 -= 1

        return min_flips