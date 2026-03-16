# Source: https://leetcode.com/problems/gcd-sort-of-an-array/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums, and you can perform the following operation any number of times on nums:
#
#
# 	Swap the positions of two elements nums[i] and nums[j] if gcd(nums[i], nums[j]) > 1 where gcd(nums[i], nums[j]) is the greatest common divisor of nums[i] and nums[j].
#
#
# Return true if it is possible to sort nums in non-decreasing order using the above swap method, or false otherwise.
#
# Example:
# Input: nums = [7,21,3]
# Output: true
# Explanation: We can sort [7,21,3] by performing the following operations:
# - Swap 7 and 21 because gcd(7,21) = 7. nums = [21,7,3]
# - Swap 21 and 3 because gcd(21,3) = 3. nums = [3,7,21]
#
# Constraints:
# 1 <= nums.length <= 3 * 104
# 	2 <= nums[i] <= 105
#

class Solution(object):
    def gcdSort(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        n = len(nums)
        max_num = max(nums)

        parent = list(range(max_num + 1))

        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]

        def union(x, y):
            parent[find(x)] = find(y)

        # Sieve of Eratosthenes to find primes and union factors
        is_prime = [True] * (max_num + 1)
        for i in range(2, max_num + 1):
            if is_prime[i]:
                for multiple in range(i * 2, max_num + 1, i):
                    is_prime[multiple] = False
                    union(i, multiple)

        # Group numbers by their root parent
        from collections import defaultdict
        groups = defaultdict(list)
        for num in nums:
            root = find(num)
            groups[root].append(num)

        # Sort each group and check if the overall array can be sorted
        sorted_nums = sorted(nums)
        index = 0
        for group in groups.values():
            group.sort()
            for num in group:
                if num != sorted_nums[index]:
                    return False
                index += 1

        return True