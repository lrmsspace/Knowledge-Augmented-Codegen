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

class Solution(object):
    def lengthAfterTransformations(self, s, t, nums):
        """
        :type s: str
        :type t: int
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7

        # Precompute the transformation matrix
        def mat_mult(A, B):
            size = len(A)
            C = [[0] * size for _ in range(size)]
            for i in range(size):
                for j in range(size):
                    for k in range(size):
                        C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD
            return C

        def mat_pow(mat, exp):
            size = len(mat)
            res = [[1 if i == j else 0 for j in range(size)] for i in range(size)]
            while exp:
                if exp % 2 == 1:
                    res = mat_mult(res, mat)
                mat = mat_mult(mat, mat)
                exp //= 2
            return res

        # Build the transformation
        size = 27  # 26 letters + 1 for length count
        transform = [[0] * size for _ in range(size)]
        for i in range(26):
            transform[i][i] = 1  # Each character contributes to itself
            transform[i][26] = nums[i]  # Each character contributes to length
        transform[26][26] = 1  # Length contributes to itself

        # Compute the transformation after t steps
        final_transform = mat_pow(transform, t)
        # Calculate the final length
        initial_length = len(s)
        final_length = 0
        for i in range(26):
            final_length = (final_length + final_transform[i][26] * s.count(chr(i + ord('a')))) % MOD
        final_length = (final_length + final_transform[26][26] * initial_length)
        return final_length % MOD   