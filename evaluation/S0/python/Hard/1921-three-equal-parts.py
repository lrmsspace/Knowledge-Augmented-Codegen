# Source: https://leetcode.com/problems/three-equal-parts/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array arr which consists of only zeros and ones, divide the array into three non-empty parts such that all of these parts represent the same binary value.
#
# If it is possible, return any [i, j] with i + 1 < j, such that:
#
#
# 	arr[0], arr[1], ..., arr[i] is the first part,
# 	arr[i + 1], arr[i + 2], ..., arr[j - 1] is the second part, and
# 	arr[j], arr[j + 1], ..., arr[arr.length - 1] is the third part.
# 	All three parts have equal binary values.
#
#
# If it is not possible, return [-1, -1].
#
# Note that the entire part is used when considering what binary value it represents. For example, [1,1,0] represents 6 in decimal, not 3. Also, leading zeros are allowed, so [0,1,1] and [1,1] represent the same value.
#
# Example:
# Input: arr = [1,0,1,0,1]
# Output: [0,3]
#
# Constraints:
# 3 <= arr.length <= 3 * 104
# 	arr[i] is 0 or 1
#

class Solution(object):
    def threeEqualParts(self, arr):
        """
        :type arr: List[int]
        :rtype: List[int]
        """
        total_ones = sum(arr)
        if total_ones % 3 != 0:
            return [-1, -1]
        if total_ones == 0:
            return [0, 2]

        ones_per_part = total_ones // 3
        first = second = third = -1
        count = 0

        for i, bit in enumerate(arr):
            if bit == 1:
                count += 1
                if count == 1:
                    first = i
                elif count == ones_per_part + 1:
                    second = i
                elif count == 2 * ones_per_part + 1:
                    third = i

        length = len(arr) - third
        if first + length <= second and second + length <= third:
            if arr[first:first + length] == arr[second:second + length] == arr[third:]:
                return [first + length - 1, second + length]
        
        return [-1, -1]