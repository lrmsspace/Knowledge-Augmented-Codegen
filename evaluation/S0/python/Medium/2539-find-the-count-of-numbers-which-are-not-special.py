# Source: https://leetcode.com/problems/find-the-count-of-numbers-which-are-not-special/   |   Difficulty: Medium
#
# Problem Description:
# You are given 2 positive integers l and r. For any number x, all positive divisors of x except x are called the proper divisors of x.
#
# A number is called special if it has exactly 2 proper divisors. For example:
#
#
# 	The number 4 is special because it has proper divisors 1 and 2.
# 	The number 6 is not special because it has proper divisors 1, 2, and 3.
#
#
# Return the count of numbers in the range [l, r] that are not special.
#
# Example:
# Input: l = 5, r = 7
#
# Output: 3
#
# Explanation:
#
# There are no special numbers in the range [5, 7].
#
# Constraints:
# 1 <= l <= r <= 109
#

class Solution(object):
    def nonSpecialCount(self, l, r):
        """
        :type l: int
        :type r: int
        :rtype: int
        """
        def is_special(n):
            count = 0
            for i in range(1, int(n**0.5) + 1):
                if n % i == 0:
                    count += 1
                    if i != n // i:
                        count += 1
                if count > 2:
                    return False
            return count == 2

        special_count = 0
        for num in range(l, r + 1):
            if is_special(num):
                special_count += 1

        return (r - l + 1) - special_count