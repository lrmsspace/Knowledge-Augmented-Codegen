# Source: https://leetcode.com/problems/find-the-longest-valid-obstacle-course-at-each-position/   |   Difficulty: Hard
#
# Problem Description:
# You want to build some obstacle courses. You are given a 0-indexed integer array obstacles of length n, where obstacles[i] describes the height of the ith obstacle.
#
# For every index i between 0 and n - 1 (inclusive), find the length of the longest obstacle course in obstacles such that:
#
#
# 	You choose any number of obstacles between 0 and i inclusive.
# 	You must include the ith obstacle in the course.
# 	You must put the chosen obstacles in the same order as they appear in obstacles.
# 	Every obstacle (except the first) is taller than or the same height as the obstacle immediately before it.
#
#
# Return an array ans of length n, where ans[i] is the length of the longest obstacle course for index i as described above.
#
# Example:
# Input: obstacles = [1,2,3,2]
# Output: [1,2,3,3]
# Explanation: The longest valid obstacle course at each position is:
# - i = 0: [1], [1] has length 1.
# - i = 1: [1,2], [1,2] has length 2.
# - i = 2: [1,2,3], [1,2,3] has length 3.
# - i = 3: [1,2,3,2], [1,2,2] has length 3.
#
# Constraints:
# n == obstacles.length
# 	1 <= n <= 105
# 	1 <= obstacles[i] <= 107
#

class Solution(object):
    def longestObstacleCourseAtEachPosition(self, obstacles):
        """
        :type obstacles: List[int]
        :rtype: List[int]
        """
        from bisect import bisect_right

        n = len(obstacles)
        dp = []
        result = []

        for height in obstacles:
            index = bisect_right(dp, height)
            if index == len(dp):
                dp.append(height)
            else:
                dp[index] = height
            result.append(index + 1)

        return result