# Source: https://leetcode.com/problems/minimum-operations-to-convert-number/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer array nums containing distinct numbers, an integer start, and an integer goal. There is an integer x that is initially set to start, and you want to perform operations on x such that it is converted to goal. You can perform the following operation repeatedly on the number x:
#
# If 0 <= x <= 1000, then for any index i in the array (0 <= i < nums.length), you can set x to any of the following:
#
#
# 	x + nums[i]
# 	x - nums[i]
# 	x ^ nums[i] (bitwise-XOR)
#
#
# Note that you can use each nums[i] any number of times in any order. Operations that set x to be out of the range 0 <= x <= 1000 are valid, but no more operations can be done afterward.
#
# Return the minimum number of operations needed to convert x = start into goal, and -1 if it is not possible.
#
# Example:
# Input: nums = [2,4,12], start = 2, goal = 12
# Output: 2
# Explanation: We can go from 2 → 14 → 12 with the following 2 operations.
# - 2 + 12 = 14
# - 14 - 2 = 12
#
# Constraints:
# 1 <= nums.length <= 1000
# 	-109 <= nums[i], goal <= 109
# 	0 <= start <= 1000
# 	start != goal
# 	All the integers in nums are distinct.
#

class Solution(object):
    def minimumOperations(self, nums, start, goal):
        """
        :type nums: List[int]
        :type start: int
        :type goal: int
        :rtype: int
        """
        from collections import deque

        queue = deque([(start, 0)])  # (current value, steps)
        visited = set()

        while queue:
            x, steps = queue.popleft()

            if x == goal:
                return steps

            if x < 0 or x > 1000 or x in visited:
                continue

            visited.add(x)

            for num in nums:
                queue.append((x + num, steps + 1))
                queue.append((x - num, steps + 1))
                queue.append((x ^ num, steps + 1))

        return -1