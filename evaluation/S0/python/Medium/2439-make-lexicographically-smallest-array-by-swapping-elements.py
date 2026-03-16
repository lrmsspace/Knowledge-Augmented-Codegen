# Source: https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array of positive integers nums and a positive integer limit.
#
# In one operation, you can choose any two indices i and j and swap nums[i] and nums[j] if |nums[i] - nums[j]| <= limit.
#
# Return the lexicographically smallest array that can be obtained by performing the operation any number of times.
#
# An array a is lexicographically smaller than an array b if in the first position where a and b differ, array a has an element that is less than the corresponding element in b. For example, the array [2,10,3] is lexicographically smaller than the array [10,2,3] because they differ at index 0 and 2 < 10.
#
# Example:
# Input: nums = [1,5,3,9,8], limit = 2
# Output: [1,3,5,8,9]
# Explanation: Apply the operation 2 times:
# - Swap nums[1] with nums[2]. The array becomes [1,3,5,9,8]
# - Swap nums[3] with nums[4]. The array becomes [1,3,5,8,9]
# We cannot obtain a lexicographically smaller array by applying any more operations.
# Note that it may be possible to get the same result by doing different operations.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 109
# 	1 <= limit <= 109
#

class Solution(object):
    def lexicographicallySmallestArray(self, nums, limit):
        """
        :type nums: List[int]
        :type limit: int
        :rtype: List[int]
        """
        n = len(nums)
        parent = list(range(n))
        rank = [1] * n

        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]

        def union(x, y):
            rootX = find(x)
            rootY = find(y)
            if rootX != rootY:
                if rank[rootX] > rank[rootY]:
                    parent[rootY] = rootX
                elif rank[rootX] < rank[rootY]:
                    parent[rootX] = rootY
                else:
                    parent[rootY] = rootX
                    rank[rootX] += 1

        for i in range(n):
            for j in range(i + 1, n):
                if abs(nums[i] - nums[j]) <= limit:
                    union(i, j)

        from collections import defaultdict
        groups = defaultdict(list)
        for i in range(n):
            root = find(i)
            groups[root].append(nums[i])

        for key in groups:
            groups[key].sort(reverse=True)

        result = []
        for i in range(n):
            root = find(i)
            result.append(groups[root].pop())

        return result