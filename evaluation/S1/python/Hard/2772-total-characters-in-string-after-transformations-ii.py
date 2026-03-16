# Source: https://leetcode.com/problems/total-characters-in-string-after-transformations-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s consisting of lowercase English letters, an integer t representing the number of transformations to perform, and an array nums of size 26. In one transformation, every character in s is replaced according to the following rules:
#
#
# 	Replace s[i] with the next nums[s[i] - 'a'] consecutive characters in the alphabet. For example, if s[i] = 'a' and nums[0] = 3, the character 'a' transforms into the next 3 consecutive characters ahead of it, which results in "bcd".
# 	The transformation wraps around the alphabet if it exceeds 'z'. For example, if s[i] = 'y' and nums[24] = 3, the character 'y' transforms into the next 3 consecutive characters ahead of it, which results in "zab".
#
#
# Return the length of the resulting string after exactly t transformations.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: s = "abcyy", t = 2, nums = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2]
#
# Output: 7
#
# Explanation:
#
#
# 	
# 	First Transformation (t = 1):
#
# 	
# 		'a' becomes 'b' as nums[0] == 1
# 		'b' becomes 'c' as nums[1] == 1
# 		'c' becomes 'd' as nums[2] == 1
# 		'y' becomes 'z' as nums[24] == 1
# 		'y' becomes 'z' as nums[24] == 1
# 		String after the first transformation: "bcdzz"
# 	
# 	
# 	
# 	Second Transformation (t = 2):
#
# 	
# 		'b' becomes 'c' as nums[1] == 1
# 		'c' becomes 'd' as nums[2] == 1
# 		'd' becomes 'e' as nums[3] == 1
# 		'z' becomes 'ab' as nums[25] == 2
# 		'z' becomes 'ab' as nums[25] == 2
# 		String after the second transformation: "cdeabab"
# 	
# 	
# 	
# 	Final Length of the string: The string is "cdeabab", which has 7 characters.
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists only of lowercase English letters.
# 	1 <= t <= 109
# 	nums.length == 26
# 	1 <= nums[i] <= 25
#
# Helpful references (internal KB):
# - Fibonacci Numbers (matrix, matrix-exp)
#   • When to use: Use when needing to compute the N-th Fibonacci number or similar linear recurrence relations for very large N efficiently, typically in logarithmic time.
#   • Idea: This method computes the N-th Fibonacci number by transforming the linear recurrence into a matrix multiplication, then using binary exponentiation (matrix exponentiation) to raise the transformation matrix to the N-th power. It achieves O(log N) time complexity.
#   • Invariants: The base matrix M = [[1, 1], [1, 0]] correctly transforms (F_k, F_{k-1}) to (F_{k+1}, F_k).; After k matrix multiplications, the accumulated matrix represents M^k.
#   • Tips: Understand binary exponentiation for matrices to efficiently compute powers.; The base transformation matrix for Fibonacci is typically [[1, 1], [1, 0]].
#   • Pitfalls: Incorrectly setting up the base matrix or initial vector.; Forgetting to apply modulo operations, leading to integer overflow for large numbers.
# - Manacher's Algorithm - Finding all sub-p (string, array, enumeration)
#   • When to use: Use when you need to find all palindromic substrings within a given string, or determine the longest palindromic substring, in optimal linear time.
#   • Idea: Manacher's Algorithm efficiently finds the length of the longest palindromic substring centered at each position in a given string, handling both odd and even lengths uniformly via preprocessing. It achieves this in optimal O(N) time complexity.
#   • Invariants: p[i] correctly stores the radius of the longest palindrome centered at i in the transformed string.; The right_boundary always marks the rightmost extent of the largest palindrome found so far.
#   • Tips: Preprocess the string with a unique delimiter to unify odd and even length palindromes.; Leverage the mirror property around the current center to initialize palindrome radii.
#   • Pitfalls: Off-by-one errors when converting `p` array values back to original string indices or lengths.; Incorrectly handling the boundaries of the preprocessed string.
# - Discrete Logarithm (array, number, binary-search, mod-exp)
#   • When to use: Use when solving for the exponent 'x' in the modular equation a^x = b (mod m), especially when 'm' is large and a and m are coprime. It's suitable for finding a solution within O(sqrt(m) log m) time.
#   • Idea: This algorithm, also known as Baby-step Giant-step, finds the smallest non-negative integer 'x' satisfying a^x = b (mod m) using a meet-in-the-middle approach. It achieves a time complexity of O(sqrt(m) log m).
#   • Invariants: The map stores (a^q mod m, q) for all baby steps q in [0, n-1].; For each giant step p, a^(np) mod m is correctly computed.
#   • Tips: Choose 'n' as ceil(sqrt(m)) for balanced steps.; Use a hash map to store baby steps for O(1) average lookup.
#   • Pitfalls: Incorrect choice of 'n' can lead to suboptimal time complexity.; Failure to check if 'a' and 'm' are coprime may yield no solution or incorrect results.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def lengthAfterTransformations(self, s, t, nums):
        """
        :type s: str
        :type t: int
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        # Precompute the length of the transformed string for each character after t transformations
        char_length = [1] * 26  # Initial length for each character is 1 (itself)
        
        for _ in range(t):
            new_char_length = [0] * 26
            for i in range(26):
                new_char_length[i] = (char_length[i] * nums[i]) % MOD
            char_length = new_char_length
        
        # Calculate the total length of the transformed string
        total_length = 0
        for char in s:
            total_length = (total_length + char_length[ord(char) - ord('a')]) % MOD
        
        return total_length