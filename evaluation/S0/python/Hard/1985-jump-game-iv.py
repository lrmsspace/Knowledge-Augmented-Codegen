# Source: https://leetcode.com/problems/jump-game-iv/   |   Difficulty: Hard
#
# Problem Description:
# Given an array of integers arr, you are initially positioned at the first index of the array.
#
# In one step you can jump from index i to index:
#
#
# 	i + 1 where: i + 1 < arr.length.
# 	i - 1 where: i - 1 >= 0.
# 	j where: arr[i] == arr[j] and i != j.
#
#
# Return the minimum number of steps to reach the last index of the array.
#
# Notice that you can not jump outside of the array at any time.
#
# Example:
# Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
# Output: 3
# Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9. Note that index 9 is the last index of the array.
#
# Constraints:
# 1 <= arr.length <= 5 * 104
# 	-108 <= arr[i] <= 108
#

class Solution(object):
    def minJumps(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        from collections import deque, defaultdict

        n = len(arr)
        if n <= 1:
            return 0

        graph = defaultdict(list)
        for i in range(n):
            graph[arr[i]].append(i)

        queue = deque([0])
        visited = set()
        visited.add(0)
        steps = 0

        while queue:
            size = len(queue)
            for _ in range(size):
                index = queue.popleft()
                if index == n - 1:
                    return steps

                neighbors = []
                if index + 1 < n:
                    neighbors.append(index + 1)
                if index - 1 >= 0:
                    neighbors.append(index - 1)
                neighbors.extend(graph[arr[index]])

                for neighbor in neighbors:
                    if neighbor not in visited:
                        visited.add(neighbor)
                        queue.append(neighbor)

                graph[arr[index]].clear()

            steps += 1

        return -1