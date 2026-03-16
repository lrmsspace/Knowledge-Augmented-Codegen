# Source: https://leetcode.com/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given a binary array nums.
#
# You can do the following operation on the array any number of times (possibly zero):
#
#
# 	Choose any 3 consecutive elements from the array and flip all of them.
#
#
# Flipping an element means changing its value from 0 to 1, and from 1 to 0.
#
# Return the minimum number of operations required to make all elements in nums equal to 1. If it is impossible, return -1.
#
# Example:
# Input: nums = [0,1,1,1,0,0]
#
# Output: 3
#
# Explanation:
# We can do the following operations:
#
#
# 	Choose the elements at indices 0, 1 and 2. The resulting array is nums = [1,0,0,1,0,0].
# 	Choose the elements at indices 1, 2 and 3. The resulting array is nums = [1,1,1,0,0,0].
# 	Choose the elements at indices 3, 4 and 5. The resulting array is nums = [1,1,1,1,1,1].
#
# Constraints:
# 3 <= nums.length <= 105
# 	0 <= nums[i] <= 1
#

class Solution(object):
    def minOperations(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        flip = [0] * (n + 1)
        curr_flip = 0
        operations = 0

        for i in range(n):
            curr_flip ^= flip[i]
            if nums[i] ^ curr_flip == 0:
                if i + 3 > n:
                    return -1
                operations += 1
                curr_flip ^= 1
                flip[i + 3] ^= 1

        return operations