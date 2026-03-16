# Source: https://leetcode.com/problems/sum-of-k-mirror-numbers/   |   Difficulty: Hard
#
# Problem Description:
# A k-mirror number is a positive integer without leading zeros that reads the same both forward and backward in base-10 as well as in base-k.
#
#
# 	For example, 9 is a 2-mirror number. The representation of 9 in base-10 and base-2 are 9 and 1001 respectively, which read the same both forward and backward.
# 	On the contrary, 4 is not a 2-mirror number. The representation of 4 in base-2 is 100, which does not read the same both forward and backward.
#
#
# Given the base k and the number n, return the sum of the n smallest k-mirror numbers.
#
# Example:
# Input: k = 2, n = 5
# Output: 25
# Explanation:
# The 5 smallest 2-mirror numbers and their representations in base-2 are listed as follows:
#   base-10    base-2
#     1          1
#     3          11
#     5          101
#     7          111
#     9          1001
# Their sum = 1 + 3 + 5 + 7 + 9 = 25.
#
# Constraints:
# 2 <= k <= 9
# 	1 <= n <= 30
#

class Solution(object):
    def kMirror(self, k, n):
        """
        :type k: int
        :type n: int
        :rtype: int
        """
        def is_palindrome(s):
            return s == s[::-1]

        def to_base(num, base):
            digits = []
            while num:
                digits.append(int(num % base))
                num //= base
            return ''.join(str(x) for x in digits[::-1]) if digits else '0'

        count = 0
        total_sum = 0
        num = 1

        while count < n:
            if is_palindrome(str(num)):
                base_k_representation = to_base(num, k)
                if is_palindrome(base_k_representation):
                    total_sum += num
                    count += 1
            num += 1

        return total_sum