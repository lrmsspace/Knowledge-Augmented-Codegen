# Source: https://leetcode.com/problems/finding-3-digit-even-numbers/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer array digits, where each element is a digit. The array may contain duplicates.
#
# You need to find all the unique integers that follow the given requirements:
#
#
# 	The integer consists of the concatenation of three elements from digits in any arbitrary order.
# 	The integer does not have leading zeros.
# 	The integer is even.
#
#
# For example, if the given digits were [1, 2, 3], integers 132 and 312 follow the requirements.
#
# Return a sorted array of the unique integers.
#
# Example:
# Input: digits = [2,1,3,0]
# Output: [102,120,130,132,210,230,302,310,312,320]
# Explanation: All the possible integers that follow the requirements are in the output array. 
# Notice that there are no odd integers or integers with leading zeros.
#
# Constraints:
# 3 <= digits.length <= 100
# 	0 <= digits[i] <= 9
#

class Solution(object):
    def findEvenNumbers(self, digits):
        """
        :type digits: List[int]
        :rtype: List[int]
        """
        from itertools import permutations

        unique_numbers = set()

        for perm in permutations(digits, 3):
            num = perm[0] * 100 + perm[1] * 10 + perm[2]
            if perm[0] != 0 and num % 2 == 0:
                unique_numbers.add(num)

        return sorted(unique_numbers)