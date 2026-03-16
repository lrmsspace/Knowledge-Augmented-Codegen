# Source: https://leetcode.com/problems/maximum-prime-difference/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums.
#
# Return an integer that is the maximum distance between the indices of two (not necessarily different) prime numbers in nums.
#
# Example:
# Input: nums = [4,2,9,5,3]
#
# Output: 3
#
# Explanation: nums[1], nums[3], and nums[4] are prime. So the answer is |4 - 1| = 3.
#
# Constraints:
# 1 <= nums.length <= 3 * 105
# 	1 <= nums[i] <= 100
# 	The input is generated such that the number of prime numbers in the nums is at least one.
#

class Solution(object):
    def maximumPrimeDifference(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def is_prime(n):
            if n <= 1:
                return False
            for i in range(2, int(n**0.5) + 1):
                if n % i == 0:
                    return False
            return True

        primes_indices = [i for i, num in enumerate(nums) if is_prime(num)]

        if not primes_indices:
            return -1

        return primes_indices[-1] - primes_indices[0]