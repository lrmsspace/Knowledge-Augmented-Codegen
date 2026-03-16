# Source: https://leetcode.com/problems/jump-game-iii/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of non-negative integers arr, you are initially positioned at start index of the array. When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach any index with value 0.
#
# Notice that you can not jump outside of the array at any time.
#
# Example:
# Input: arr = [4,2,3,0,3,1,2], start = 5
# Output: true
# Explanation: 
# All possible ways to reach at index 3 with value 0 are: 
# index 5 -> index 4 -> index 1 -> index 3 
# index 5 -> index 6 -> index 4 -> index 1 -> index 3
#
# Constraints:
# 1 <= arr.length <= 5 * 104
# 	0 <= arr[i] < arr.length
# 	0 <= start < arr.length
#

class Solution(object):
    def canReach(self, arr, start):
        """
        :type arr: List[int]
        :type start: int
        :rtype: bool
        """
        n = len(arr)
        visited = [False] * n
        
        def dfs(index):
            if index < 0 or index >= n or visited[index]:
                return False
            if arr[index] == 0:
                return True
            
            visited[index] = True
            
            return dfs(index + arr[index]) or dfs(index - arr[index])
        
        return dfs(start)