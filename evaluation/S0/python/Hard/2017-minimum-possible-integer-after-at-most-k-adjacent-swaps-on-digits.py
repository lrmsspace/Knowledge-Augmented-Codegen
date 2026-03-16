# Source: https://leetcode.com/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string num representing the digits of a very large integer and an integer k. You are allowed to swap any two adjacent digits of the integer at most k times.
#
# Return the minimum integer you can obtain also as a string.
#
# Example:
# Input: num = "4321", k = 4
# Output: "1342"
# Explanation: The steps to obtain the minimum integer from 4321 with 4 adjacent swaps are shown.
#
# Constraints:
# 1 <= num.length <= 3 * 104
# 	num consists of only digits and does not contain leading zeros.
# 	1 <= k <= 109
#

class Solution(object):
    def minInteger(self, num, k):
        """
        :type num: str
        :type k: int
        :rtype: str
        """
        from sortedcontainers import SortedList
        n = len(num)
        pos = [[] for _ in range(10)]
        for i, c in enumerate(num):
            pos[int(c)].append(i)
        
        bit = [0] * (n + 1)
        
        def update(i):
            while i <= n:
                bit[i] += 1
                i += i & -i
        
        def query(i):
            s = 0
            while i > 0:
                s += bit[i]
                i -= i & -i
            return s
        
        res = []
        for _ in range(n):
            for digit in range(10):
                if pos[digit]:
                    idx = pos[digit][0]
                    cost = idx - query(idx + 1)
                    if cost <= k:
                        k -= cost
                        res.append(str(digit))
                        update(idx + 1)
                        pos[digit].pop(0)
                        break
        return ''.join(res)