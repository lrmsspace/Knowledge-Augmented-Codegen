# Source: https://leetcode.com/problems/prime-in-diagonal/   |   Difficulty: Easy
#
# Problem Description:
# You are given a 0-indexed two-dimensional integer array nums.
#
# Return the largest prime number that lies on at least one of the diagonals of nums. In case, no prime is present on any of the diagonals, return 0.
#
# Note that:
#
#
# 	An integer is prime if it is greater than 1 and has no positive integer divisors other than 1 and itself.
# 	An integer val is on one of the diagonals of nums if there exists an integer i for which nums[i][i] = val or an i for which nums[i][nums.length - i - 1] = val.
#
#
#
#
# In the above diagram, one diagonal is [1,5,9] and another diagonal is [3,5,7].
#
# Example:
# Input: nums = [[1,2,3],[5,6,7],[9,10,11]]
# Output: 11
# Explanation: The numbers 1, 3, 6, 9, and 11 are the only numbers present on at least one of the diagonals. Since 11 is the largest prime, we return 11.
#
# Constraints:
# 1 <= nums.length <= 300
# 	nums.length == numsi.length
# 	1 <= nums[i][j] <= 4*106
#

class Solution(object):
    def diagonalPrime(self, nums):
        """
        :type nums: List[List[int]]
        :rtype: int
        """
        def is_prime(n):
            if n <= 1:
                return False
            if n <= 3:
                return True
            if n % 2 == 0 or n % 3 == 0:
                return False
            i = 5
            while i * i <= n:
                if n % i == 0 or n % (i + 2) == 0:
                    return False
                i += 6
            return True

        max_prime = 0
        n = len(nums)

        for i in range(n):
            # Check primary diagonal
            if is_prime(nums[i][i]):
                max_prime = max(max_prime, nums[i][i])
            # Check secondary diagonal
            if is_prime(nums[i][n - i - 1]):
                max_prime = max(max_prime, nums[i][n - i - 1])

        return max_prime