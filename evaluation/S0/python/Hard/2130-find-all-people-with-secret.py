# Source: https://leetcode.com/problems/find-all-people-with-secret/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer n indicating there are n people numbered from 0 to n - 1. You are also given a 0-indexed 2D integer array meetings where meetings[i] = [xi, yi, timei] indicates that person xi and person yi have a meeting at timei. A person may attend multiple meetings at the same time. Finally, you are given an integer firstPerson.
#
# Person 0 has a secret and initially shares the secret with a person firstPerson at time 0. This secret is then shared every time a meeting takes place with a person that has the secret. More formally, for every meeting, if a person xi has the secret at timei, then they will share the secret with person yi, and vice versa.
#
# The secrets are shared instantaneously. That is, a person may receive the secret and share it with people in other meetings within the same time frame.
#
# Return a list of all the people that have the secret after all the meetings have taken place. You may return the answer in any order.
#
# Example:
# Input: n = 6, meetings = [[1,2,5],[2,3,8],[1,5,10]], firstPerson = 1
# Output: [0,1,2,3,5]
# Explanation:
# At time 0, person 0 shares the secret with person 1.
# At time 5, person 1 shares the secret with person 2.
# At time 8, person 2 shares the secret with person 3.
# At time 10, person 1 shares the secret with person 5.​​​​
# Thus, people 0, 1, 2, 3, and 5 know the secret after all the meetings.
#
# Constraints:
# 2 <= n <= 105
# 	1 <= meetings.length <= 105
# 	meetings[i].length == 3
# 	0 <= xi, yi <= n - 1
# 	xi != yi
# 	1 <= timei <= 105
# 	1 <= firstPerson <= n - 1
#

class Solution(object):
    def findAllPeople(self, n, meetings, firstPerson):
        """
        :type n: int
        :type meetings: List[List[int]]
        :type firstPerson: int
        :rtype: List[int]
        """
        from collections import defaultdict, deque

        parent = list(range(n))
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        def union(x, y):
            rootX = find(x)
            rootY = find(y)
            if rootX != rootY:
                parent[rootY] = rootX

        union(0, firstPerson)
        meetings.sort(key=lambda x: x[2])
        i = 0
        while i < len(meetings):
            time = meetings[i][2]
            temp_parent = parent[:]
            j = i
            participants = set()
            while j < len(meetings) and meetings[j][2] == time:
                x, y, _ = meetings[j]
                participants.add(x)
                participants.add(y)
                union(x, y)
                j += 1
            for p in participants:
                if find(p) != find(0):
                    parent[p] = temp_parent[p]
            i = j
        result = []
        for person in range(n):
            if find(person) == find(0):
                result.append(person)
        return result   