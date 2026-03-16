# Source: https://leetcode.com/problems/remove-methods-from-project/   |   Difficulty: Medium
#
# Problem Description:
# You are maintaining a project that has n methods numbered from 0 to n - 1.
#
# You are given two integers n and k, and a 2D integer array invocations, where invocations[i] = [ai, bi] indicates that method ai invokes method bi.
#
# There is a known bug in method k. Method k, along with any method invoked by it, either directly or indirectly, are considered suspicious and we aim to remove them.
#
# A group of methods can only be removed if no method outside the group invokes any methods within it.
#
# Return an array containing all the remaining methods after removing all the suspicious methods. You may return the answer in any order. If it is not possible to remove all the suspicious methods, none should be removed.
#
# Example:
# Input: n = 4, k = 1, invocations = [[1,2],[0,1],[3,2]]
#
# Output: [0,1,2,3]
#
# Explanation:
#
#
#
# Method 2 and method 1 are suspicious, but they are directly invoked by methods 3 and 0, which are not suspicious. We return all elements without removing anything.
#
# Constraints:
# 1 <= n <= 105
# 	0 <= k <= n - 1
# 	0 <= invocations.length <= 2 * 105
# 	invocations[i] == [ai, bi]
# 	0 <= ai, bi <= n - 1
# 	ai != bi
# 	invocations[i] != invocations[j]
#

class Solution(object):
    def remainingMethods(self, n, k, invocations):
        """
        :type n: int
        :type k: int
        :type invocations: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict, deque

        graph = defaultdict(list)
        indegree = [0] * n

        for a, b in invocations:
            graph[a].append(b)
            indegree[b] += 1

        suspicious = set()
        queue = deque([k])
        suspicious.add(k)

        while queue:
            method = queue.popleft()
            for neighbor in graph[method]:
                if neighbor not in suspicious:
                    suspicious.add(neighbor)
                    queue.append(neighbor)

        for method in suspicious:
            if indegree[method] > 0:
                return list(range(n))

        return [i for i in range(n) if i not in suspicious]