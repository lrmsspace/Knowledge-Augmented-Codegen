# Source: https://leetcode.com/problems/course-schedule-ii/   |   Difficulty: Medium
#
# Problem Description:
# There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.
#
#
# 	For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
#
#
# Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.
#
# Example:
# Input: numCourses = 2, prerequisites = [[1,0]]
# Output: [0,1]
# Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].
#
# Constraints:
# 1 <= numCourses <= 2000
# 	0 <= prerequisites.length <= numCourses * (numCourses - 1)
# 	prerequisites[i].length == 2
# 	0 <= ai, bi < numCourses
# 	ai != bi
# 	All the pairs [ai, bi] are distinct.
#

class Solution(object):
    def findOrder(self, numCourses, prerequisites):
        """
        :type numCourses: int
        :type prerequisites: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict, deque

        graph = defaultdict(list)
        in_degree = [0] * numCourses

        for course, prereq in prerequisites:
            graph[prereq].append(course)
            in_degree[course] += 1

        zero_in_degree = deque([i for i in range(numCourses) if in_degree[i] == 0])
        order = []

        while zero_in_degree:
            node = zero_in_degree.popleft()
            order.append(node)

            for neighbor in graph[node]:
                in_degree[neighbor] -= 1
                if in_degree[neighbor] == 0:
                    zero_in_degree.append(neighbor)

        if len(order) == numCourses:
            return order
        else:
            return []