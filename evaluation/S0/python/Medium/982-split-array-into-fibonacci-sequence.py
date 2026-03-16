# Source: https://leetcode.com/problems/split-array-into-fibonacci-sequence/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string of digits num, such as "123456579". We can split it into a Fibonacci-like sequence [123, 456, 579].
#
# Formally, a Fibonacci-like sequence is a list f of non-negative integers such that:
#
#
# 	0 <= f[i] < 231, (that is, each integer fits in a 32-bit signed integer type),
# 	f.length >= 3, and
# 	f[i] + f[i + 1] == f[i + 2] for all 0 <= i < f.length - 2.
#
#
# Note that when splitting the string into pieces, each piece must not have extra leading zeroes, except if the piece is the number 0 itself.
#
# Return any Fibonacci-like sequence split from num, or return [] if it cannot be done.
#
# Example:
# Input: num = "1101111"
# Output: [11,0,11,11]
# Explanation: The output [110, 1, 111] would also be accepted.
#
# Constraints:
# 1 <= num.length <= 200
# 	num contains only digits.
#

class Solution(object):
    def splitIntoFibonacci(self, num):
        """
        :type num: str
        :rtype: List[int]
        """
        n = len(num)
        for i in range(1, min(10, n)):
            for j in range(i + 1, min(i + 10, n)):
                a, b = num[:i], num[i:j]
                if (a.startswith('0') and len(a) > 1) or (b.startswith('0') and len(b) > 1):
                    continue
                a, b = int(a), int(b)
                fib = [a, b]
                k = j
                while k < n:
                    c = a + b
                    c_str = str(c)
                    if not num.startswith(c_str, k):
                        break
                    fib.append(c)
                    k += len(c_str)
                    a, b = b, c
                if k == n and len(fib) >= 3:
                    return fib
        return []