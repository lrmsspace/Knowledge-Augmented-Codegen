# Source: https://leetcode.com/problems/maximum-segment-sum-after-removals/   |   Difficulty: Hard
#
# Problem Description:
# You are given two 0-indexed integer arrays nums and removeQueries, both of length n. For the ith query, the element in nums at the index removeQueries[i] is removed, splitting nums into different segments.
#
# A segment is a contiguous sequence of positive integers in nums. A segment sum is the sum of every element in a segment.
#
# Return an integer array answer, of length n, where answer[i] is the maximum segment sum after applying the ith removal.
#
# Note: The same index will not be removed more than once.
#
# Example:
# Input: nums = [1,2,5,6,1], removeQueries = [0,3,2,4,1]
# Output: [14,7,2,2,0]
# Explanation: Using 0 to indicate a removed element, the answer is as follows:
# Query 1: Remove the 0th element, nums becomes [0,2,5,6,1] and the maximum segment sum is 14 for segment [2,5,6,1].
# Query 2: Remove the 3rd element, nums becomes [0,2,5,0,1] and the maximum segment sum is 7 for segment [2,5].
# Query 3: Remove the 2nd element, nums becomes [0,2,0,0,1] and the maximum segment sum is 2 for segment [2]. 
# Query 4: Remove the 4th element, nums becomes [0,2,0,0,0] and the maximum segment sum is 2 for segment [2]. 
# Query 5: Remove the 1st element, nums becomes [0,0,0,0,0] and the maximum segment sum is 0, since there are no segments.
# Finally, we return [14,7,2,2,0].
#
# Constraints:
# n == nums.length == removeQueries.length
# 	1 <= n <= 105
# 	1 <= nums[i] <= 109
# 	0 <= removeQueries[i] < n
# 	All the values of removeQueries are unique.
#

class Solution(object):
    def maximumSegmentSum(self, nums, removeQueries):
        """
        :type nums: List[int]
        :type removeQueries: List[int]
        :rtype: List[int]
        """
        n = len(nums)
        parent = list(range(n))
        size = [0] * n
        total = [0] * n

        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]

        def union(x, y):
            rootX = find(x)
            rootY = find(y)
            if rootX != rootY:
                parent[rootY] = rootX
                size[rootX] += size[rootY]
                total[rootX] += total[rootY]

        answer = []
        max_sum = 0
        active = [False] * n

        for i in range(n - 1, -1, -1):
            idx = removeQueries[i]
            active[idx] = True
            size[idx] = 1
            total[idx] = nums[idx]

            if idx > 0 and active[idx - 1]:
                union(idx, idx - 1)
            if idx < n - 1 and active[idx + 1]:
                union(idx, idx + 1)

            root = find(idx)
            max_sum = max(max_sum, total[root])
            answer.append(max_sum)

        return answer[::-1]