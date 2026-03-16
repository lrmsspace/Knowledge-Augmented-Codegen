# Source: https://leetcode.com/problems/greatest-common-divisor-traversal/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed integer array nums, and you are allowed to traverse between its indices. You can traverse between index i and index j, i != j, if and only if gcd(nums[i], nums[j]) > 1, where gcd is the greatest common divisor.
#
# Your task is to determine if for every pair of indices i and j in nums, where i < j, there exists a sequence of traversals that can take us from i to j.
#
# Return true if it is possible to traverse between all such pairs of indices, or false otherwise.
#
# Example:
# Input: nums = [2,3,6]
# Output: true
# Explanation: In this example, there are 3 possible pairs of indices: (0, 1), (0, 2), and (1, 2).
# To go from index 0 to index 1, we can use the sequence of traversals 0 -> 2 -> 1, where we move from index 0 to index 2 because gcd(nums[0], nums[2]) = gcd(2, 6) = 2 > 1, and then move from index 2 to index 1 because gcd(nums[2], nums[1]) = gcd(6, 3) = 3 > 1.
# To go from index 0 to index 2, we can just go directly because gcd(nums[0], nums[2]) = gcd(2, 6) = 2 > 1. Likewise, to go from index 1 to index 2, we can just go directly because gcd(nums[1], nums[2]) = gcd(3, 6) = 3 > 1.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 105
#

class Solution(object):
    def canTraverseAllPairs(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        max_num = max(nums)
        parent = list(range(max_num + 1))
        
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            rootX = find(x)
            rootY = find(y)
            if rootX != rootY:
                parent[rootY] = rootX
        
        spf = list(range(max_num + 1))
        for i in range(2, int(max_num**0.5) + 1):
            if spf[i] == i:
                for j in range(i * i, max_num + 1, i):
                    if spf[j] == j:
                        spf[j] = i
        
        for num in nums:
            original_num = num
            factors = set()
            while num > 1:
                factors.add(spf[num])
                num //= spf[num]
            factors = list(factors)
            for factor in factors[1:]:
                union(factors[0], factor)
            union(original_num, factors[0])
        
        root = find(nums[0])
        for num in nums[1:]:
            if find(num) != root:
                return False
        return True