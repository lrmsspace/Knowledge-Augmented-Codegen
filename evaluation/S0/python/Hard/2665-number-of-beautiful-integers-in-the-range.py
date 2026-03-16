# Source: https://leetcode.com/problems/number-of-beautiful-integers-in-the-range/   |   Difficulty: Hard
#
# Problem Description:
# You are given positive integers low, high, and k.
#
# A number is beautiful if it meets both of the following conditions:
#
#
# 	The count of even digits in the number is equal to the count of odd digits.
# 	The number is divisible by k.
#
#
# Return the number of beautiful integers in the range [low, high].
#
# Example:
# Input: low = 10, high = 20, k = 3
# Output: 2
# Explanation: There are 2 beautiful integers in the given range: [12,18]. 
# - 12 is beautiful because it contains 1 odd digit and 1 even digit, and is divisible by k = 3.
# - 18 is beautiful because it contains 1 odd digit and 1 even digit, and is divisible by k = 3.
# Additionally we can see that:
# - 16 is not beautiful because it is not divisible by k = 3.
# - 15 is not beautiful because it does not contain equal counts even and odd digits.
# It can be shown that there are only 2 beautiful integers in the given range.
#
# Constraints:
# 0 < low <= high <= 109
# 	0 < k <= 20
#

class Solution(object):
    def numberOfBeautifulIntegers(self, low, high, k):
        """
        :type low: int
        :type high: int
        :type k: int
        :rtype: int
        """
        def count_beautiful(num):
            s = str(num)
            n = len(s)
            from functools import lru_cache

            @lru_cache(None)
            def dp(i, even_count, odd_count, mod, is_limit, is_num):
                if i == n:
                    return 1 if even_count == odd_count and is_num and mod == 0 else 0

                res = 0
                if not is_num:
                    res += dp(i + 1, even_count, odd_count, mod, False, False)

                up = int(s[i]) if is_limit else 9
                for d in range(0 if is_num else 1, up + 1):
                    res += dp(i + 1,
                              even_count + (1 if d % 2 == 0 else 0),
                              odd_count + (1 if d % 2 == 1 else 0),
                              (mod * 10 + d) % k,
                              is_limit and d == up,
                              True)
                return res

            return dp(0, 0, 0, 0, True, False)

        return count_beautiful(high) - count_beautiful(low - 1)