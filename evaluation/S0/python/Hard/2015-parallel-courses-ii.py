# Source: https://leetcode.com/problems/parallel-courses-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer n, which indicates that there are n courses labeled from 1 to n. You are also given an array relations where relations[i] = [prevCoursei, nextCoursei], representing a prerequisite relationship between course prevCoursei and course nextCoursei: course prevCoursei has to be taken before course nextCoursei. Also, you are given the integer k.
#
# In one semester, you can take at most k courses as long as you have taken all the prerequisites in the previous semesters for the courses you are taking.
#
# Return the minimum number of semesters needed to take all courses. The testcases will be generated such that it is possible to take every course.
#
# Example:
# Input: n = 4, relations = [[2,1],[3,1],[1,4]], k = 2
# Output: 3
# Explanation: The figure above represents the given graph.
# In the first semester, you can take courses 2 and 3.
# In the second semester, you can take course 1.
# In the third semester, you can take course 4.
#
# Constraints:
# 1 <= n <= 15
# 	1 <= k <= n
# 	0 <= relations.length <= n * (n-1) / 2
# 	relations[i].length == 2
# 	1 <= prevCoursei, nextCoursei <= n
# 	prevCoursei != nextCoursei
# 	All the pairs [prevCoursei, nextCoursei] are unique.
# 	The given graph is a directed acyclic graph.
#

class Solution(object):
    def minNumberOfSemesters(self, n, relations, k):
        """
        :type n: int
        :type relations: List[List[int]]
        :type k: int
        :rtype: int
        """
        prereq = [0] * n
        for u, v in relations:
            prereq[v - 1] |= 1 << (u - 1)

        dp = [float('inf')] * (1 << n)
        dp[0] = 0

        for mask in range(1 << n):
            can_take = 0
            for i in range(n):
                if (mask & (1 << i)) == 0 and (mask & prereq[i]) == prereq[i]:
                    can_take |= 1 << i

            submask = can_take
            while submask:
                if bin(submask).count('1') <= k:
                    dp[mask | submask] = min(dp[mask | submask], dp[mask] + 1)
                submask = (submask - 1) & can_take

        return dp[(1 << n) - 1]