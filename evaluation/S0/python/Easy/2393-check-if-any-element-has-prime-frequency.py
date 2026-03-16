# Source: https://leetcode.com/problems/check-if-any-element-has-prime-frequency/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer array nums.
#
# Return true if the frequency of any element of the array is prime, otherwise, return false.
#
# The frequency of an element x is the number of times it occurs in the array.
#
# A prime number is a natural number greater than 1 with only two factors, 1 and itself.
#
# Example:
# Input: nums = [1,2,3,4,5,4]
#
# Output: true
#
# Explanation:
#
# 4 has a frequency of two, which is a prime number.
#
# Constraints:
# 1 <= nums.length <= 100
# 	0 <= nums[i] <= 100
#

class Solution(object):
    def checkPrimeFrequency(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        from collections import Counter
        def is_prime(n):
            if n <= 1:
                return False
            for i in range(2, int(n**0.5) + 1):
                if n % i == 0:
                    return False
            return True

        freq = Counter(nums)
        for count in freq.values():
            if is_prime(count):
                return True
        return False