# Source: https://leetcode.com/problems/minimum-incompatibility/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums​​​ and an integer k. You are asked to distribute this array into k subsets of equal size such that there are no two equal elements in the same subset.
#
# A subset's incompatibility is the difference between the maximum and minimum elements in that array.
#
# Return the minimum possible sum of incompatibilities of the k subsets after distributing the array optimally, or return -1 if it is not possible.
#
# A subset is a group integers that appear in the array with no particular order.
#
# Example:
# Input: nums = [1,2,1,4], k = 2
# Output: 4
# Explanation: The optimal distribution of subsets is [1,2] and [1,4].
# The incompatibility is (2-1) + (4-1) = 4.
# Note that [1,1] and [2,4] would result in a smaller sum, but the first subset contains 2 equal elements.
#
# Constraints:
# 1 <= k <= nums.length <= 16
# 	nums.length is divisible by k
# 	1 <= nums[i] <= nums.length
#

class Solution(object):
    def minimumIncompatibility(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        from itertools import combinations
        from functools import lru_cache

        n = len(nums)
        subset_size = n // k

        # Check if it's possible to form k subsets without duplicates
        if any(nums.count(x) > k for x in set(nums)):
            return -1

        all_indices = range(n)
        valid_subsets = []

        # Generate all valid subsets of size subset_size
        for indices in combinations(all_indices, subset_size):
            subset = [nums[i] for i in indices]
            if len(set(subset)) == subset_size:  # No duplicates in the subset
                valid_subsets.append((indices, max(subset) - min(subset)))

        @lru_cache(None)
        def dp(used_mask):
            if used_mask == (1 << n) - 1:
                return 0  # All elements are used

            min_incompatibility = float('inf')

            for indices, incompatibility in valid_subsets:
                subset_mask = sum(1 << i for i in indices)
                if used_mask & subset_mask == 0:  # Subset can be used
                    result = dp(used_mask | subset_mask)
                    if result != -1:
                        min_incompatibility = min(min_incompatibility, result + incompatibility)

            return min_incompatibility if min_incompatibility != float('inf') else -1

        return dp(0)