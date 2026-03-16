# Source: https://leetcode.com/problems/total-characters-in-string-after-transformations-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s and an integer t, representing the number of transformations to perform. In one transformation, every character in s is replaced according to the following rules:
#
#
# 	If the character is 'z', replace it with the string "ab".
# 	Otherwise, replace it with the next character in the alphabet. For example, 'a' is replaced with 'b', 'b' is replaced with 'c', and so on.
#
#
# Return the length of the resulting string after exactly t transformations.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: s = "abcyy", t = 2
#
# Output: 7
#
# Explanation:
#
#
# 	First Transformation (t = 1):
#
# 	
# 		'a' becomes 'b'
# 		'b' becomes 'c'
# 		'c' becomes 'd'
# 		'y' becomes 'z'
# 		'y' becomes 'z'
# 		String after the first transformation: "bcdzz"
# 	
# 	
# 	Second Transformation (t = 2):
# 	
# 		'b' becomes 'c'
# 		'c' becomes 'd'
# 		'd' becomes 'e'
# 		'z' becomes "ab"
# 		'z' becomes "ab"
# 		String after the second transformation: "cdeabab"
# 	
# 	
# 	Final Length of the string: The string is "cdeabab", which has 7 characters.
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists only of lowercase English letters.
# 	1 <= t <= 105
#
# Helpful references (internal KB):
# - Suffix Array (string, array, counting-sort, radix-sort)
#   • When to use: Use when you need to efficiently query or analyze all suffixes of a string, often for pattern matching, string searching, or finding repeated substrings. It provides a sorted order of all suffixes.
#   • Idea: The Suffix Array algorithm constructs an array containing the starting indices of all suffixes of a string, sorted lexicographically. It typically uses a doubling strategy with counting sort or radix sort in each step, achieving an O(N log N) time complexity.
#   • Invariants: After iteration k, p contains the sorted indices of all cyclic substrings of length 2^k.; After iteration k, c[i] represents the equivalence class of the cyclic substring starting at i with length 2^k.
#   • Tips: Append a unique, smallest character (e.g., '$') to the string to handle suffixes as cyclic shifts.; Utilize counting sort for efficient sorting of characters and pairs of equivalence classes.
#   • Pitfalls: Incorrectly handling the sentinel character can lead to incorrect suffix order or out-of-bounds access.; Off-by-one errors when calculating indices for cyclic shifts or substring lengths.
# - Finding repetitions (string, array, z-function, enumeration)
#   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
#   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
#   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
#   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
#   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
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
    def lengthAfterTransformations(self, s, t):
        """
        :type s: str
        :type t: int
        :rtype: int
        """
        MOD = 10**9 + 7
        
        # Precompute the length contributions for each character after t transformations
        dp = [0] * 26  # dp[i] will hold the length contribution of character chr(i + ord('a'))
        
        for i in range(26):
            if i == 25:  # 'z'
                dp[i] = 2  # 'z' -> "ab"
            else:
                dp[i] = 1  # other characters -> next character
        
        # Apply transformations t times
        for _ in range(t):
            new_dp = [0] * 26
            for i in range(26):
                if i == 25:  # 'z'
                    new_dp[i] = (dp[0] + dp[1]) % MOD  # 'z' -> "ab"
                else:
                    new_dp[i] = dp[i + 1] % MOD  # other characters -> next character
            dp = new_dp
        
        # Calculate the final length of the string after t transformations
        result_length = 0
        for char in s:
            index = ord(char) - ord('a')
            result_length = (result_length + dp[index]) % MOD
        
        return result_length