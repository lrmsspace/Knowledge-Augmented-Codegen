# Source: https://leetcode.com/problems/largest-component-size-by-common-factor/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array of unique positive integers nums. Consider the following graph:
#
#
# 	There are nums.length nodes, labeled nums[0] to nums[nums.length - 1],
# 	There is an undirected edge between nums[i] and nums[j] if nums[i] and nums[j] share a common factor greater than 1.
#
#
# Return the size of the largest connected component in the graph.
#
# Example:
# Input: nums = [4,6,15,35]
# Output: 4
#
# Constraints:
# 1 <= nums.length <= 2 * 104
# 	1 <= nums[i] <= 105
# 	All the values of nums are unique.
#

class Solution(object):
    def largestComponentSize(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        parent = {}
        size = {}

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

        def get_factors(n):
            factors = set()
            for i in range(2, int(n**0.5) + 1):
                while n % i == 0:
                    factors.add(i)
                    n //= i
            if n > 1:
                factors.add(n)
            return factors

        for num in nums:
            parent[num] = num
            size[num] = 1

        factor_map = {}
        for num in nums:
            factors = get_factors(num)
            for factor in factors:
                if factor in factor_map:
                    union(num, factor_map[factor])
                factor_map[factor] = num

        return max(size.values())