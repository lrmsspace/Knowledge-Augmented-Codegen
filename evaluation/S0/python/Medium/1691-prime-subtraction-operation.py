# Source: https://leetcode.com/problems/prime-subtraction-operation/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer array nums of length n.
#
# You can perform the following operation as many times as you want:
#
#
# 	Pick an index i that you haven’t picked before, and pick a prime p strictly less than nums[i], then subtract p from nums[i].
#
#
# Return true if you can make nums a strictly increasing array using the above operation and false otherwise.
#
# A strictly increasing array is an array whose each element is strictly greater than its preceding element.
#
# Example:
# Input: nums = [4,9,6,10]
# Output: true
# Explanation: In the first operation: Pick i = 0 and p = 3, and then subtract 3 from nums[0], so that nums becomes [1,9,6,10].
# In the second operation: i = 1, p = 7, subtract 7 from nums[1], so nums becomes equal to [1,2,6,10].
# After the second operation, nums is sorted in strictly increasing order, so the answer is true.
#
# Constraints:
# 1 <= nums.length <= 1000
# 	1 <= nums[i] <= 1000
# 	nums.length == n
#

class Solution(object):
    def primeSubOperation(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        def is_prime(n):
            if n <= 1:
                return False
            for i in range(2, int(n**0.5) + 1):
                if n % i == 0:
                    return False
            return True

        primes = [i for i in range(2, 1000) if is_prime(i)]
        prev = 0

        for i in range(len(nums)):
            found = False
            for p in reversed(primes):
                if p < nums[i] and nums[i] - p > prev:
                    nums[i] -= p
                    prev = nums[i]
                    found = True
                    break
            if not found:
                if nums[i] > prev:
                    prev = nums[i]
                else:
                    return False

        return True