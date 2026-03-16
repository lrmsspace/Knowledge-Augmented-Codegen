# Source: https://leetcode.com/problems/course-schedule/   |   Difficulty: Medium
#
# Problem Description:
# There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.
#
#
# 	For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
#
#
# Return true if you can finish all courses. Otherwise, return false.
#
# Example:
# Input: numCourses = 2, prerequisites = [[1,0]]
# Output: true
# Explanation: There are a total of 2 courses to take. 
# To take course 1 you should have finished course 0. So it is possible.
#
# Constraints:
# 1 <= numCourses <= 2000
# 	0 <= prerequisites.length <= 5000
# 	prerequisites[i].length == 2
# 	0 <= ai, bi < numCourses
# 	All the pairs prerequisites[i] are unique.
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def canFinish(self, numCourses, prerequisites):
        """
        :type numCourses: int
        :type prerequisites: List[List[int]]
        :rtype: bool
        """
        from collections import defaultdict
        
        graph = defaultdict(list)
        for course, prereq in prerequisites:
            graph[prereq].append(course)
        
        visited = [0] * numCourses  # 0 = unvisited, 1 = visiting, 2 = visited
        
        def dfs(course):
            if visited[course] == 1:  # Found a cycle
                return False
            if visited[course] == 2:  # Already fully processed
                return True
            
            visited[course] = 1  # Mark as visiting
            for neighbor in graph[course]:
                if not dfs(neighbor):
                    return False
            visited[course] = 2  # Mark as visited
            return True
        
        for course in range(numCourses):
            if not dfs(course):
                return False
        
        return True