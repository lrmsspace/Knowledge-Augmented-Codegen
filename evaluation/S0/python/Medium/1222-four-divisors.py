# Source: https://leetcode.com/problems/four-divisors/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums, return the sum of divisors of the integers in that array that have exactly four divisors. If there is no such integer in the array, return 0.
#
# Example:
# Input: nums = [21,4,7]
# Output: 32
# Explanation: 
# 21 has 4 divisors: 1, 3, 7, 21
# 4 has 3 divisors: 1, 2, 4
# 7 has 2 divisors: 1, 7
# The answer is the sum of divisors of 21 only.
#
# Constraints:
# 1 <= nums.length <= 104
# 	1 <= nums[i] <= 105
#

class Solution(object):
    def sumFourDivisors(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def get_divisors_count_and_sum(n):
            count = 0
            total_sum = 0
            for i in range(1, int(n**0.5) + 1):
                if n % i == 0:
                    count += 1
                    total_sum += i
                    if i != n // i:
                        count += 1
                        total_sum += n // i
                if count > 4:
                    return 0, 0
            return count, total_sum

        result = 0
        for num in nums:
            count, total_sum = get_divisors_count_and_sum(num)
            if count == 4:
                result += total_sum

        return result